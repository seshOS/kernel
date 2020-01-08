#include <stdio.h>
#include <kernel/serial.h>

void output_to_serial(char character, void *) {
	sesh::Serial(0).Write(character);
}

extern "C" void kernel_main() {
	sesh::Serial serial(0);
	serial.Init();
	serial.WriteString("[INFO] Serial initialised.\n");
	
	fctprintf(output_to_serial, (void *)0, "[INFO] Hello, World! kernel_main is at: %p\n", kernel_main);
	while (1);
}
