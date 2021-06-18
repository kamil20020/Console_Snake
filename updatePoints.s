.text

.global updatePoints

updatePoints:

push %ebp
mov %esp, %ebp

mov 8(%ebp), %edx	# &points
mov 12(%ebp), %ecx	# gained
add %ecx, (%edx)	# points = points + gained

exit:
pop %ebp
ret
