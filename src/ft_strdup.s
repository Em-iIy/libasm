section .text

extern ft_strlen
extern ft_strcpy
extern malloc

global ft_strdup

;char *ft_strdup(const char *s)
; ret = rax
; *str = rdi

ft_strdup:
	push	rdi					; save input string on stack
	call	ft_strlen			; get length of input string
	inc		rax					; get length + 1 for null terminator
	mov		rdi, rax			; move length to malloc parameter
	call	malloc wrt ..plt	; malloc
	cmp		rax, 0x0			; check malloc return
	jz		.error
	mov		rdi, rax			; move allocated pointer to strcpy 1st parameter
	pop		rsi					; retrieve input string from stack int 2nd parameter
	call 	ft_strcpy			; strcpy
	ret

.error:
	pop		rdi					; pop stack in case of malloc error for allignment
	ret