#include <stdio.h>
#include <kernel/serial.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/irq.h>

extern "C" void kernel_main() {
	sesh::Serial serial(0);
	serial.Init();
	printf("[INFO] Serial initialised.\n");
	printf("[INFO] Hello, World! kernel_main is at: %p\n", kernel_main);
	
	sesh::GlobalDescriptorTable gdt;
	gdt.Init();
	printf("[INFO] GDT initialised.\n");
	
	sesh::InterruptDescriptorTable idt;
	idt.Init();
	printf("[INFO] Interrupt handlers installed\n");
	while (1);
}
