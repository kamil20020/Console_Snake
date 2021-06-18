.text

.global collider

collider:

push %ebp
mov %esp, %ebp

checkFirstX:
mov 8(%ebp), %ecx	# firstX
add 24(%ebp), %ecx	# firstSize
cmp 16(%ebp), %ecx	# firstX + firstSize > secondX
JG checkSecondX
jmp not

checkSecondX:
mov 16(%ebp), %edx	# secondX
add 28(%ebp), %edx	# secondX + secondSize
cmp %edx, 8(%ebp)	# firstX < secondX + secondSize
JL checkFirstY
jmp not

checkFirstY:
mov 12(%ebp), %ecx	# firstY
add 24(%ebp), %ecx	# firstSize
cmp 20(%ebp), %ecx	# firstY + firstSize > secondY
JG checkSecondY
jmp not

checkSecondY:
mov 20(%ebp), %edx	# secondY
add 28(%ebp), %edx	# secondY + secondSize
cmp %edx, 12(%ebp)	# firstY < secondY + secondSize
JL yes
jmp not

yes:
mov $1, %eax
jmp exit

not:
mov $0, %eax

exit:
pop %ebp
ret
