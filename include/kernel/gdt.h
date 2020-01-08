#ifndef __KERNEL_GDT_H
#define __KERNEL_GDT_H

#include <stdint.h>

namespace sesh {
	struct SegmentDescriptor {
		uint16_t limit_low;
		uint16_t base_low;
		uint8_t base_mid;
		uint8_t access;
		uint8_t limit_high : 4;
		uint8_t flags : 4;
		uint8_t base_high;

		void SetLimit(uint32_t lim);
		void SetBase(uint32_t base);
	} __attribute__((packed));

	class GlobalDescriptorTable {
		SegmentDescriptor entries[5];

	public:
		GlobalDescriptorTable();

		void Init();
	};
}

#endif//__KERNEL_GDT_H
