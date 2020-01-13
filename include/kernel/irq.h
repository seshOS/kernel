#ifndef __KERNEL_IRQ_H_
#define __KERNEL_IRQ_H_

#include <kernel/idt.h>

namespace sesh {
	namespace irq {
		void InstallHandlers(InterruptDescriptorTable *idt);		
	}
}

#endif//__KERNEL_IRQ_H_