#ifndef __KERNEL_ISR_H_
#define __KERNEL_ISR_H_

#include <kernel/idt.h>

namespace sesh {
	namespace isr {
		void InstallHandlers(InterruptDescriptorTable *idt);		
	}
}

#endif//__KERNEL_ISR_H_