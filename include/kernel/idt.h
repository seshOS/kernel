#ifndef __KERNEL_IDT_H_
#define __KERNEL_IDT_H_

#include <stdint.h>

namespace sesh {
    struct InterruptFrame {
		uint32_t gs, fd, es, ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
		uint32_t interrupt_number, error_code;
		uint32_t eip, cs, eflags, user_esp, ss;
	};

	struct InterruptDescriptor {
		uint16_t offset_low;
		uint16_t selector;
		uint8_t : 8;
		union {
			struct {
				uint8_t type: 4;
				uint8_t attributes: 4;
			};

			uint8_t type_attr;
		};
		uint16_t offset_high;
	} __attribute__((packed));
    
	class InterruptDescriptorTable {
		InterruptDescriptor entries[256];

	public:
		InterruptDescriptorTable();

		void SetEntry(int n, void (*function)(InterruptFrame *, uint32_t), uint8_t type_attr);

		void Load();
	};
}

#endif//__KERNEL_IDT_H_