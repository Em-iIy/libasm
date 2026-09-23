section .text

global ft_strcmp

;int	ft_strcmp(const char *s1, const char *s2)
; return = rax - (s1[i] - s2[i])
; *s1 = rdi
; *s2 = rsi


ft_strcmp:
	xor	rax, rax
	xor	r10, r10
	xor	r11, r11

.loop:
	mov	r10b, byte [rdi + rax]	; store s1[rax] in r10
	mov	r11b, byte [rsi + rax]	; store s2[rax] in r11

	cmp	r10b, 0x0				; check for null terminator
	je	.return					; return

	inc	rax						; increment rax
	cmp	r10b, r11b				; compare s1[rax] and s2[rax]
	je	.loop					; if they're equal, loop again

.return:
	sub	r10, r11				; subtract s2[rax] from s1[rax] (stored in r10)
	mov	rax, r10				; move result to rax
	ret
