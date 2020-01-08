#include <stdio.h>
#include <stdint.h>

void _putchar(char character) {
	uint16_t *const video_memory = (uint16_t *)0xC00B8000;
	static unsigned int cursor_x = 0, cursor_y = 0;

	switch (character) {
		case '\n':
			cursor_y++;
		case '\r':
			cursor_x = 0;
			return;

		default:
			break;
	}

	video_memory[cursor_x + cursor_y * 80] = 0x0700 | character;
	cursor_x++;
	
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}

	if (cursor_y >= 24) {
		for (unsigned y = 0; y < 24; ++y) {
			for (unsigned x = 0; x < 80; ++x) {
				video_memory[x + y * 80] = video_memory[x + (y + 1) * 80];
			}
		}

		cursor_y = 23;
	}
}
