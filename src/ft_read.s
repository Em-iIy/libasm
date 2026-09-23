section .text

extern __errno_location

global ft_read

; ssize_t read(int fd, void *buf, size_t count)
;  ret = rax (bytes read or -1)
;  fd = rdi
;  *buf = rsi
;  count = rdx

ft_read:
	mov	rax, 0
	syscall
	cmp	rax, 0x0	; check if return was less than 0
	jl	.error		; set errno
	ret

.error:
	neg	rax			; get positive value of the error
	mov	rdi, rax	; save value
	call __errno_location wrt ..plt ; get errno address into rax
	mov [rax], rdi	; set errno
	mov	rax, -1		; set return to -1
	ret