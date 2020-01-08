#ifndef __KERNEL_PORT_H_
#define __KERNEL_PORT_H_

#include <stdint.h>

namespace sesh {
	class Port {
		uint16_t num;

	public:
		Port(uint16_t number = 0);
	
		uint8_t Read8() const;
		uint16_t Read16() const;
		uint32_t Read32() const;

		void Write8(uint8_t data) const;
		void Write8Slow(uint8_t data) const;
		void Write16(uint16_t data) const;
		void Write32(uint32_t data) const;

		Port operator+(const uint16_t &rhs) const;
	};
}

#endif//__KERNEL_PORT_H_
