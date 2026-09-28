section .text

global ft_strcpy

;char *ft_strcpy(char *dest, const char *src)
; ret = rax - returns dest pointer
; *dest = rdi
; *src = rsi

ft_strcpy:
	xor	rax, rax	; set rax to 0

.loop:
	mov	r10b, byte [rsi + rax]	; get char at src[rax] in r10b
	mov	[rdi + rax], r10b		; store char at r10b in dest[rax]
	inc	rax						
	cmp	r10b, 0x0				; check null terminator
	jnz .loop					; loop if (src[rax] != 0)

.return:
	mov	rax, rdi	; store dest pointer in return
	ret