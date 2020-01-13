#include <kernel/idt.h>
#include <kernel/gdt.h> // sesh::DescriptorTablePointer

namespace sesh {
	InterruptDescriptorTable::InterruptDescriptorTable() {}

	void InterruptDescriptorTable::SetEntry(int n, void (*function)(InterruptFrame *, uint32_t), uint8_t type_attr) {
		entries[n].offset_low = ((uint32_t)function) & 0xFFFF;
		entries[n].offset_high = (((uint32_t)function) >> 16) & 0xFFFF;
		entries[n].type_attr = type_attr;
		entries[n].selector = 0x08;
	}

	void InterruptDescriptorTable::Load() {
		DescriptorTablePointer pointer;
		pointer.address = (uint32_t)entries;
		pointer.size = sizeof(entries) - 1;
		asm volatile("lidt %0; sti" :: "m"(pointer));
	}
}