#include <kernel/gdt.h>
#include <stdio.h>
#include <kernel/serial.h>

namespace sesh {
	void SegmentDescriptor::SetLimit(uint32_t lim) {
		if (lim >= 0x100000) {
			if ((lim & 0xFFF) != 0xFFF) {
			//	printf("[WARNING] loss of precision on limit 0x%X\n", lim);
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

	void GlobalDescriptorTable::SetEntry(int n, uint32_t base, uint32_t limit, uint8_t access) {
		entries[n].SetBase(base);
		entries[n].SetLimit(limit);
		entries[n].access = access;
	}

	void GlobalDescriptorTable::Load() {
		DescriptorTablePointer pointer;
		pointer.address = (uint32_t)entries;
		pointer.size = sizeof(entries) - 1;
		asm volatile("lgdt %0" :: "m"(pointer));
	}

	void GlobalDescriptorTable::Init() {
		SetEntry(0, 0x00000000, 0x00000000, 0x00); // null
		SetEntry(1, 0x00000000, 0xFFFFFFFF, 0x9A); // kernel code
		SetEntry(2, 0x00000000, 0xFFFFFFFF, 0x92); // kernel data
		SetEntry(3, 0x00000000, 0xFFFFFFFF, 0xFA); // user code
		SetEntry(4, 0x00000000, 0xFFFFFFFF, 0xF2); // user data
		
		Load();
	}
}
