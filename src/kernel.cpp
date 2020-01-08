#include <stdio.h>
#include <kernel/serial.h>

void output_to_serial(char character, void *) {
	sesh::Serial(0).Write(character);
}

extern "C" void kernel_main() {
	fctprintf(output_to_serial, (void *)0, "Hello, World!\n");
	while (1);
}
