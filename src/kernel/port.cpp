#include <kernel/port.h>

namespace sesh {
	Port::Port(uint16_t number) : num(number) {}

	uint8_t Port::Read8() const {
		uint8_t result;
		asm volatile("inb %1, %0" : "=a"(result) : "Nd"(num));
		return result;
	}

	uint16_t Port::Read16() const {
		uint16_t result;
		asm volatile("inw %1, %0" : "=a"(result) : "Nd"(num));
		return result;
	}
	
	uint32_t Port::Read32() const {
		uint32_t result;
		asm volatile("inl %1, %0" : "=a"(result) : "Nd"(num));
		return result;
	}

	void Port::Write8(uint8_t data) const {
		asm volatile("outb %0, %1" :: "a"(data), "Nd"(num));
	}

	void Port::Write8Slow(uint8_t data) const {
		asm volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" :: "a"(data), "Nd"(num));
	}
	
	void Port::Write16(uint16_t data) const {
		asm volatile("outw %0, %1" :: "a"(data), "Nd"(num));
	}

	void Port::Write32(uint32_t data) const {
		asm volatile("outl %0, %1" :: "a"(data), "Nd"(num));
	}

	Port Port::operator+(const uint16_t &rhs) const {
		return Port(num + rhs);
	}
}
