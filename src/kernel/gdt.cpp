#include <kernel/gdt.h>
#include <stdio.h>
#include <kernel/serial.h>

namespace sesh {
	void SegmentDescriptor::SetLimit(uint32_t lim) {
		if (lim >= 0x100000) {
			if ((lim & 0xFFF) != 0x000) {
				serial_printf(0, "[WARNING] loss of precision on limit 0x%X\n", lim);
			}

			lim >>= 12;
			flags = 0xC;
		} else {
			flags = 0x4;
		}

		limit_low = lim & 0xFFFF;
		limit_high = (lim >> 16) & 0xF;
	}

	void SegmentDescriptor::SetBase(uint32_t base) {
		base_low = base & 0xFFFF;
		base_mid = (base >> 16) & 0xFF;
		base_high = (base >> 24) & 0xFF;
	}

	GlobalDescriptorTable::GlobalDescriptorTable() {}

	void GlobalDescriptorTable::Init() {
		// null
		entries[0].SetBase(0x00000000);
		entries[0].SetLimit(0xFFFFFFFF);
		entries[0].access = 0x00;

		// kernel code
		entries[1].SetBase(0x00000000);
		entries[1].SetLimit(0xFFFFFFFF);
		entries[1].access = 0x9A;
		
		// kernel data
		entries[2].SetBase(0x00000000);
		entries[2].SetLimit(0xFFFFFFFF);
		entries[2].access = 0x92;
		
		// user code
		entries[3].SetBase(0x00000000);
		entries[3].SetLimit(0xFFFFFFFF);
		entries[3].access = 0xFA;

		// user data
		entries[4].SetBase(0x00000000);
		entries[4].SetLimit(0xFFFFFFFF);
		entries[4].access = 0xF2;

		// load the thing
		struct { uint32_t address; uint16_t size; } __attribute__((packed)) pointer;
		pointer.address = (uint32_t)entries;
		pointer.size = sizeof(entries) - 1;
		asm volatile("lgdt %0" :: "m"(pointer));
	}
}
