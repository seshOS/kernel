#include <kernel/serial.h>

namespace sesh {
	static const uint16_t __serial_ports[4] = { 0x3F8, 0x2F8, 0x3E8, 0x2E8 };

	Serial::Serial(int port_idx) : data(__serial_ports[port_idx]) {
		status = data + 5;
	}

	void Serial::Init() const {
		(data + 1).Write8(0x00);
		(data + 3).Write8(0x80);
		(data + 0).Write8(0x03);
		(data + 1).Write8(0x00);
		(data + 3).Write8(0x03);
		(data + 2).Write8(0xC7);
		(data + 4).Write8(0x0B);
	}

	void Serial::Write(uint8_t c) const {
		while (!TransmitEmpty());

		if (c == '\n') {
			Write('\r');
		}
		data.Write8(c);
	}
	
	void Serial::WriteString(const char *s) const {
		while (*s) {
			Write(*s++);
		}
	}

	uint8_t Serial::Read() const {
		while (!Received());

		return data.Read8();
	}

	bool Serial::Received() const {
		return status.Read8() & 0x01;
	}

	bool Serial::TransmitEmpty() const {
		return status.Read8() & 0x20;
	}
}
