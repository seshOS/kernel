#ifndef __KERNEL_SERIAL_H_
#define __KERNEL_SERIAL_H_

#include <stdint.h>
#include <kernel/port.h>

namespace sesh {
	class Serial {
		Port data, status;
		int port_no;

	public:
		Serial(int port_index);

		void Init() const;

		void Write(uint8_t c) const;
		uint8_t Read() const;
		
		bool Received() const;
		bool TransmitEmpty() const;
	};
}

#endif//__KERNEL_SERIAL_H_
