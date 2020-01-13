#include <kernel/isr.h>
#include <stdio.h>

namespace sesh {
	namespace isr {
		void InstallHandlers(InterruptDescriptorTable *idt) {
			#define INSTALL_ISR_HANDLER(n) \
				void __isr##n##_handler();\
				idt->SetEntry(n, (void *)__isr##n##_handler, 0x8E);

			INSTALL_ISR_HANDLER(0x00);
			INSTALL_ISR_HANDLER(0x01);
			INSTALL_ISR_HANDLER(0x02);
			INSTALL_ISR_HANDLER(0x03);
			INSTALL_ISR_HANDLER(0x04);
			INSTALL_ISR_HANDLER(0x05);
			INSTALL_ISR_HANDLER(0x06);
			INSTALL_ISR_HANDLER(0x07);
			INSTALL_ISR_HANDLER(0x08);
			INSTALL_ISR_HANDLER(0x09);
			INSTALL_ISR_HANDLER(0x0A);
			INSTALL_ISR_HANDLER(0x0B);
			INSTALL_ISR_HANDLER(0x0C);
			INSTALL_ISR_HANDLER(0x0D);
			INSTALL_ISR_HANDLER(0x0E);
			INSTALL_ISR_HANDLER(0x0F);
			INSTALL_ISR_HANDLER(0x10);
			INSTALL_ISR_HANDLER(0x11);
			INSTALL_ISR_HANDLER(0x12);
			INSTALL_ISR_HANDLER(0x13);
			INSTALL_ISR_HANDLER(0x14);
			INSTALL_ISR_HANDLER(0x15);
			INSTALL_ISR_HANDLER(0x16);
			INSTALL_ISR_HANDLER(0x17);
			INSTALL_ISR_HANDLER(0x18);
			INSTALL_ISR_HANDLER(0x19);
			INSTALL_ISR_HANDLER(0x1A);
			INSTALL_ISR_HANDLER(0x1B);
			INSTALL_ISR_HANDLER(0x1C);
			INSTALL_ISR_HANDLER(0x1D);
			INSTALL_ISR_HANDLER(0x1E);
			INSTALL_ISR_HANDLER(0x1F);

			#undef INSTALL_ISR_HANDLER
		}

		void ISRHandler(InterruptFrame *frame) {
			const char *error_messages[] = {
				"Division by zero", "Debug", "NMI", "Breakpoint",
				"Overflow", "Bound range exceeded", "Invalid opcode", "Device not available",
				"Double fault", "Coprocessor segment overrun", "Invalid TSS", "Segment not present",
				"Stack-Segment fault", "General Protection Fault", "Page Fault", "Reserved",
				"Floating-point exception", "Alignment check", "Machine check", "SIMD exception",
				"Virtualisation exception", "Reserved", "Reserved", "Reserved",
				"Reserved", "Reserved", "Reserved", "Reserved",
				"Reserved", "Reserved", "Security exception", "Reserved"
			};

			printf("[ERROR] ISR Handler called\nReason: %s\nEIP:0x%x\n", error_messages[frame->interrupt_number], frame->eip);
			printf("Error code: %x", frame->error_code);
			while (1);
		}
	}	
}