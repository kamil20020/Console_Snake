.text

.global updateHeadAfterMoveLogic

updateHeadAfterMoveLogic:

push %ebp
mov %esp, %ebp

mov 8(%ebp), %edx	# direction

cmp $1, %edx
JE direction1

cmp $2, %edx
JE direction2

cmp $3, %edx
JE direction3

cmp $4, %edx
JE direction4

# headY >= 1
direction1:
mov 16(%ebp), %edx	# bodyY
mov (%edx), %ecx	# headY
cmp $1, %ecx		
JL skip
sub $1, (%edx)
jmp next

# headY <= fieldY
direction2:
mov 16(%ebp), %edx	# bodyY
mov (%edx), %ecx	# headY
cmp 24(%ebp), %ecx	# fieldY
JG skip
add $1, (%edx)
jmp next

# headX >= 1
direction3:
mov 12(%ebp), %edx	# bodyX
mov (%edx), %ecx	# headX
cmp $1, %ecx
JL skip
sub $1, (%edx)
jmp next

# headX <= fieldX - 3
direction4:
mov 12(%ebp), %edx	# bodyX
mov (%edx), %ecx	# headX
cmp 20(%ebp), %ecx	# fieldX
JG skip
add $1, (%edx)

next:
mov $1, %eax
jmp exit

skip:
mov $0, %eax

exit:
pop %ebp
ret
