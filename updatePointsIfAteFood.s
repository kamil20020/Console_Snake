.text

.global updatePointsIfAteFood

updatePointsIfAteFood:

push %ebp
mov %esp, %ebp

checkFirst:
mov 8(%ebp), %ecx	# headX
cmp 16(%ebp), %ecx	# foodX
JE checkSecond
jmp not

checkSecond:
mov 12(%ebp), %ecx	# headY
cmp 20(%ebp), %ecx	# foodY
JE yes
jmp not

yes:
mov 24(%ebp), %edx	# &points
add $1, (%edx)
mov $1, %eax
jmp exit

not:
mov $0, %eax

exit:
pop %ebp
ret
