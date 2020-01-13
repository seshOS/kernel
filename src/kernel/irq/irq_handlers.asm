	extern _ZN4sesh3irq10IRQHandlerEPNS_14InterruptFrameE
	global __irq_stub
__irq_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	call _ZN4sesh3irq10IRQHandlerEPNS_14InterruptFrameE
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

%macro irq 1
	global _ZN4sesh3irq17__irq%1_handlerEv
_ZN4sesh3irq17__irq%1_handlerEv:
	cli
	push byte 0
	push byte %1 + 32
	jmp __irq_stub
%endmacro

irq 0x00
irq 0x01
irq 0x02
irq 0x03
irq 0x04
irq 0x05
irq 0x06
irq 0x07
irq 0x08
irq 0x09
irq 0x0A
irq 0x0B
irq 0x0C
irq 0x0D
irq 0x0E
irq 0x0F