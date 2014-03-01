; boot.s
[ORG 0x7c00]
jmp main

%include "print.inc"

main:
	xor ax, ax
	mov ds, ax
	mov si, msg
	call print
hang:
	jmp hang

msg	db 'Welcome to Macintosh', 10, 13, 'hi', 0
; 10 --> \n
; 13 --> \r
	times 510-($-$$) db 0
	db 0x55
	db 0xAA
