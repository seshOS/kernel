extern "C" void kernel_main() {
	*(unsigned short *)0xC00B8000 = 0x0765;
	while (1);
}
