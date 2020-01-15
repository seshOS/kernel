#include <kernel/idt.h>
#include <kernel/gdt.h> // sesh::DescriptorTablePointer
#include <kernel/isr.h>
#include <kernel/irq.h>

namespace sesh {
	InterruptDescriptorTable::InterruptDescriptorTable() : pic1_cmd(0x20), pic2_cmd(0xA0) {
		pic1_data = pic1_cmd + 1;
		pic2_data = pic2_cmd + 1;
	}

	void InterruptDescriptorTable::SetEntry(int n, void *function, uint8_t type_attr) {
		entries[n].offset_low = ((uint32_t)function) & 0xFFFF;
		entries[n].offset_high = (((uint32_t)function) >> 16) & 0xFFFF;
		entries[n].type_attr = type_attr;
		entries[n].selector = 0x08;
	}

	void InterruptDescriptorTable::Load() {
		DescriptorTablePointer pointer;
		pointer.address = (uint32_t)entries;
		pointer.size = sizeof(entries) - 1;

		uint8_t mask1, mask2;
		mask1 = pic1_data.Read8();
		mask2 = pic2_data.Read8();

		pic1_cmd.Write8(0x11);
		pic2_cmd.Write8(0x11);
		pic1_data.Write8(0x20);
		pic2_data.Write8(0x28);
		pic1_data.Write8(4);
		pic2_data.Write8(2);

		pic1_data.Write8(0x01);
		pic2_data.Write8(0x01);

		pic1_data.Write8(mask1);
		pic2_data.Write8(mask2);

		asm volatile("lidt %0; sti" :: "m"(pointer));
	}

	void InterruptDescriptorTable::Init() {
		isr::InstallHandlers(this);
		irq::InstallHandlers(this);
		Load();		
	}
}