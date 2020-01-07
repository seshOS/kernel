MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .bootstrap_stack
align 16
stack_bottom:
	resb 16384 ; 16 KiB

global stack_top
stack_top:

section .bss
align 4096
init_page_directory:
	resb 4096

init_page_table_1:
	resb 4096

section .text
extern kernel_main
global _start
_start:
	mov edi, init_page_table_1
	sub edi, 0xC0000000
	mov esi, 0
	mov ecx, 1023
.fill_page_table:
	mov edx, esi
	or edx, 3
	mov [edi], edx
	add esi, 4096
	add edi, 4
	loop .fill_page_table
.enable_paging:
	; set up page directory
	mov edi, init_page_directory
	sub edi, 0xC0000000
	mov edx, init_page_table_1
	sub edx, 0xC0000000
	add edx, 3
	mov [edi], edx
	add edi, 3072
	mov [edi], edx

	; actually enable paging
	mov eax, init_page_directory
	sub eax, 0xC0000000
	mov cr3, eax
	mov eax, cr0
	or eax, 0x80010000
	mov cr0, eax
	lea eax, [.after_paging]
	jmp eax
.after_paging:
	; unmap the identity paging
	mov dword[init_page_directory], 0
	mov eax, cr3
	mov cr3, eax

	; call the kernel
	mov esp, stack_top
	call kernel_main
.halt_loop:
	cli
	hlt
	jmp .halt_loop
