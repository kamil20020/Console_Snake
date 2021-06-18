.text

.global updateHeadAfterMoveLogic

updateHeadAfterMoveLogic:

push %ebp
mov %esp, %ebp

mov 8(%ebp), %edx	# direction
mov 20(%ebp), %ecx 	# speed

cmp $1, %edx
JE direction1

cmp $2, %edx
JE direction2

cmp $3, %edx
JE direction3

cmp $4, %edx
JE direction4

direction1:
mov 16(%ebp), %edx	# bodyY
sub %ecx, (%edx)
jmp exit

direction2:
mov 16(%ebp), %edx	# bodyY
add %ecx, (%edx)
jmp exit

direction3:
mov 12(%ebp), %edx	# bodyX
sub %ecx, (%edx)
jmp exit

direction4:
mov 12(%ebp), %edx	# bodyX
add %ecx, (%edx)

exit:
pop %ebp
ret
