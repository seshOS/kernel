#include <stdio.h>
#include <kernel/serial.h>
#include <kernel/gdt.h>

extern "C" void kernel_main() {
	sesh::Serial serial(0);
	serial.Init();
	serial.WriteString("[INFO] Serial initialised.\n");
	serial_printf(0, "[INFO] Hello, World! kernel_main is at: %p\n", kernel_main);
	
	sesh::GlobalDescriptorTable gdt;
	gdt.Init();
	serial_printf(0, "[INFO] GDT initialised.\n");
	while (1);
}
