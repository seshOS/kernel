#include <kernel/irq.h>
#include <stdio.h>

namespace sesh {
	namespace irq {
		void InstallHandlers(InterruptDescriptorTable *idt) {
			#define INSTALL_IRQ_HANDLER(n) \
				void __irq##n##_handler();\
				idt->SetEntry(n+32, (void *)__irq##n##_handler, 0x8E);

			INSTALL_IRQ_HANDLER(0x00);
			INSTALL_IRQ_HANDLER(0x01);
			INSTALL_IRQ_HANDLER(0x02);
			INSTALL_IRQ_HANDLER(0x03);
			INSTALL_IRQ_HANDLER(0x04);
			INSTALL_IRQ_HANDLER(0x05);
			INSTALL_IRQ_HANDLER(0x06);
			INSTALL_IRQ_HANDLER(0x07);
			INSTALL_IRQ_HANDLER(0x08);
			INSTALL_IRQ_HANDLER(0x09);
			INSTALL_IRQ_HANDLER(0x0A);
			INSTALL_IRQ_HANDLER(0x0B);
			INSTALL_IRQ_HANDLER(0x0C);
			INSTALL_IRQ_HANDLER(0x0D);
			INSTALL_IRQ_HANDLER(0x0E);
			INSTALL_IRQ_HANDLER(0x0F);

			#undef INSTALL_IRQ_HANDLER
		}

		void IRQHandler(InterruptFrame *frame) {
			// hack
			// for some reason, instead of pushing 0x08,
			// it pushes 0x10.
			if (frame->cs == 0x10) {
				frame->cs = 0x8;
			}
		
			if (frame->interrupt_number >= 0x28) {
				Port(0xA0).Write8(0x20);
			}
			Port(0x20).Write8(0x20);
		}
	}	
}