	extern _ZN4sesh3isr10ISRHandlerEPNS_14InterruptFrameE
	global __isr_stub
__isr_stub:
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
	call _ZN4sesh3isr10ISRHandlerEPNS_14InterruptFrameE
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

%macro isr_with_error 1
	global _ZN4sesh3isr17__isr%1_handlerEv
_ZN4sesh3isr17__isr%1_handlerEv:
	cli
	push byte %1
	jmp __isr_stub
%endmacro

%macro isr_without_error 1
	global _ZN4sesh3isr17__isr%1_handlerEv
_ZN4sesh3isr17__isr%1_handlerEv:
	cli
	push byte 0
	push byte %1
	jmp __isr_stub
%endmacro

isr_without_error 0x00
isr_without_error 0x01
isr_without_error 0x02
isr_without_error 0x03
isr_without_error 0x04
isr_without_error 0x05
isr_without_error 0x06
isr_without_error 0x07
isr_with_error 0x08
isr_without_error 0x09
isr_with_error 0x0A
isr_with_error 0x0B
isr_with_error 0x0C
isr_with_error 0x0D
isr_with_error 0x0E
isr_without_error 0x0F 
isr_without_error 0x10
isr_without_error 0x11
isr_without_error 0x12
isr_without_error 0x13
isr_without_error 0x14
isr_without_error 0x15
isr_without_error 0x16
isr_without_error 0x17
isr_without_error 0x18
isr_without_error 0x19
isr_without_error 0x1A
isr_without_error 0x1B
isr_without_error 0x1C
isr_without_error 0x1D
isr_with_error 0x1E
isr_without_error 0x1F