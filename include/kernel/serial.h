#ifndef __KERNEL_SERIAL_H_
#define __KERNEL_SERIAL_H_

#include <stdint.h>
#include <kernel/port.h>

#define serial_printf(serial_no, fmt, ...) fctprintf(sesh::__serial_printf_stream, (void *)serial_no, fmt, ##__VA_ARGS__)

namespace sesh {
	class Serial {
		Port data, status;
		int port_no;

	public:
		Serial(int port_index);

		void Init() const;

		void Write(uint8_t c) const;
		void WriteString(const char *s) const;
		uint8_t Read() const;
		
		bool Received() const;
		bool TransmitEmpty() const;
	};

	void __serial_printf_stream(char character, void *serial_no);
}

#endif//__KERNEL_SERIAL_H_
