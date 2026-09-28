section .text

global ft_strlen

;size_t ft_strlen(const char *str)
; ret = rax
; *str = rdi

ft_strlen:
	xor rax, rax				; set rax to 0
.loop:
	cmp byte [rdi + rax], 0x0	; compare str[rax] with 0
	jz .return					; jump if equal to .return
	inc rax						; increment counter
	jmp .loop					; loop back
.return:
	ret							; return