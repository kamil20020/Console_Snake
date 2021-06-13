.text

.global updateTailAfterIncrease

updateTailAfterIncrease:

push %ebp
mov %esp, %ebp

mov 12(%ebp), %ecx	# lastBodyX
mov 16(%ebp), %esi	# lastBodyY

mov 8(%ebp), %edx	# direction

cmp $1, %edx
JE direction1

cmp $2, %edx
JE direction2

cmp $3, %edx
JE direction3

cmp $4, %edx
JE direction4

direction1:
mov 20(%ebp), %eax	# prevLastBodyX
mov %eax, (%ecx)

mov 24(%ebp), %eax	# prevLastBodyY
inc %eax
mov %eax, (%esi)
jmp exit


direction2:
mov 20(%ebp), %eax	# prevLastBodyX
mov %eax, (%ecx)

mov 24(%ebp), %eax	# prevLastBodyY
dec %eax
mov %eax, (%esi)
jmp exit


direction3:
mov 20(%ebp), %eax	# prevLastBodyX
inc	%eax
mov %eax, (%ecx)

mov 24(%ebp), %eax	# prevLastBodyY
mov %eax, (%esi)
jmp exit


direction4:
mov 20(%ebp), %eax	# prevLastBodyX
dec %eax
mov %eax, (%ecx)

mov 24(%ebp), %eax	# prevLastBodyY
mov %eax, (%esi)

exit:
pop %ebp
ret
