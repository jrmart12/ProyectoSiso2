    .global _syscall_printString
    .global _syscall_readString
    .global _syscall_readSector
	.global _syscall_readFile
	.global _syscall_executeProgram
	.global _syscall_terminate
	.global _syscall_clearScreen
	.global _syscall_deleteFile
	.global _syscall_writeFile
	.global _syscall_killProcess
_syscall_readFile:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov cx,[bp+6]
    mov bx,[bp+4]
    mov ax,#0x3
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	pop bp
	ret

_syscall_executeProgram:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov cx,0
    mov bx,[bp+4]
    mov ax,#0x4
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	pop bp
	ret

_syscall_terminate:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov ax,#0x5
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	pop bp
	ret
_syscall_deleteFile:
	push bp
	mov bp,sp
	mov dx, #0
	mov cx, #0
    mov bx,[bp+4]
    mov ax,#0x7
	int #0x21
	leave
	ret
_syscall_clearScreen:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov ax,#0xA
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	pop bp
	ret
_syscall_printString:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov bx,[bp+4]
    mov ax,#0x0
	int #0x21

	pop cx
	pop bx
	pop ax	
    pop ds
	pop bp
	ret

_syscall_readString:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx
	
    mov bx,[bp+4]
    mov ax,#0x1
	int #0x21
	
	pop cx
	pop bx
	pop ax
    pop ds
	pop bp
	ret

_syscall_readSector:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx

    mov cx,[bp+6]
    mov bx,[bp+4]
    mov ax,#0x2
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	pop bp
	ret
_syscall_writeFile:
    push bp
	mov bp,sp
	push ds
	push ax
	push bx
	push cx
	push dx

	mov dx,[bp+8]
    mov cx,[bp+6]
    mov bx,[bp+4]
    mov ax,#0x8
	int #0x21

	leave
	ret
_syscall_killProcess:
	push bp
	mov bp, sp
	push ds
	push ax
	push bx
	push cx
	
	mov bx, [bp+4]
	mov ax, #0x9
	int #0x21

	pop cx
	pop bx
	pop ax
	pop ds
	mov sp, bp
	pop bp
	ret
