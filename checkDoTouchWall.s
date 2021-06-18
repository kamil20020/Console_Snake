.text

.global checkDoTouchWall

checkDoTouchWall:

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

# headY < 0
direction1:
cmp $0, 16(%ebp)	# headY
JL yes
jmp not

# headY + headSize > fieldY
direction2:
mov 16(%ebp), %ecx	# headY
add 28(%ebp), %ecx	# headY = headY + size
cmp 24(%ebp), %ecx	# fieldY
JG yes
jmp not

# headX < 0
direction3:
cmp $1, 12(%ebp)	# headX
JL yes
jmp not

# headX + headSize > fieldX
direction4:
mov 12(%ebp), %ecx	# headX
add 28(%ebp), %ecx	# headX = headX + size
cmp 20(%ebp), %ecx	# fieldX
JG yes
jmp not

yes:
mov $1, %eax
jmp exit

not:
mov $0, %eax

exit:
pop %ebp
ret
