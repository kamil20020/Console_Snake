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

# headY < 1
direction1:
cmp $1, 16(%ebp)	# headY
JL yes
jmp not

# headY > fieldY
direction2:
mov 16(%ebp), %ecx	# headY
cmp 24(%ebp), %ecx	# fieldY
JG yes
jmp not

# headX < 1
direction3:
cmp $1, 12(%ebp)	# headX
JL yes
jmp not

# headX >= fieldX+1	
direction4:
mov 20(%ebp), %ecx	# headX
inc %ecx
cmp %ecx, 12(%ebp)	# fieldX
JGE yes
jmp not

yes:
mov $1, %eax
jmp exit

not:
mov $0, %eax

exit:
pop %ebp
ret
