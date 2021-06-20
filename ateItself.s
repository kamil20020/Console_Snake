.text

.global ateItself

ateItself:

push %ebp
mov %esp, %ebp

mov $1, %ecx					# lindex tablicy

mov 8(%ebp), %esi 				# sizeBody
mov 12(%ebp), %edx				# bodyX
mov 16(%ebp), %eax				# bodyY
mov $0, %edi					# indeks pierwszego elementu tablicy

loop:
push (%edx, %edi, 4)			# headX
push (%edx, %edi, 4)			# headY
push (%edx, %ecx, 4)			# bodyX[%ecx]
push (%edx, %ecx, 4)			# bodyY[%ecx]
push 20(%ebp)					# rozmiar grafiki ciała weza
call collider
add $20, %esp					# zdjecie argumentow ze stosu
cmp $1, %eax
JE yes
inc %ecx
cmp %esi, %ecx
JL loop

mov $0, %eax
jmp exit

yes:
mov $1, %eax					

exit:
pop %ebp
ret
