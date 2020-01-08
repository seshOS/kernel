#ifndef __KERNEL_PORT_H
#define __KERNEL_PORT_H

#include <stdint.h>

namespace sesh {
	class Port {
		uint16_t num;

	public:
		Port(uint16_t number);
	
		uint8_t Read8() const;
		uint16_t Read16() const;
		uint32_t Read32() const;

		void Write8(uint8_t data) const;
		void Write8Slow(uint8_t data) const;
		void Write16(uint16_t data) const;
		void Write32(uint32_t data) const;
	};
}

#endif//__KERNEL_PORT_H
