#include <stdio.h>

extern "C" void kernel_main() {
	printf("Hello, World!\n");
	while (1);
}
