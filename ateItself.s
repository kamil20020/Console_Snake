.text

.global ateItself

ateItself:

push %ebp
mov %esp, %ebp

mov $1, %ecx					# licznik petli

mov 8(%ebp), %esi 				# sizeBody
mov 12(%ebp), %edx				# bodyX
mov 16(%ebp), %eax				# bodyY

loop:
mov 12(%ebp), %edi
mov (%edi), %edi
cmp (%edx, %ecx, 4), %edi
JNE firstFalse

mov 16(%ebp), %edi
mov (%edi), %edi
cmp (%eax, %ecx, 4), %edi
JE yes

firstFalse:	
inc %ecx
dec %esi
cmp $0, %esi
JGE loop

mov $0, %eax
jmp exit

yes:
mov $1, %eax					

exit:
pop %ebp
ret
