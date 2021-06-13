.text

.global updateBodyAfterMove

updateBodyAfterMove:

push %ebp
mov %esp, %ebp

mov $1, %ecx					# indeks tablic

loop:
mov %ecx, %edi
dec %edi

mov 12(%ebp), %edx				# bodyX
lea (%edx, %ecx, 4), %edx
mov 20(%ebp), %esi				# prevBodyX
mov (%esi, %edi, 4), %esi
mov %esi, (%edx)

mov 16(%ebp), %edx				# bodyY
lea (%edx, %ecx, 4), %edx
mov 24(%ebp), %esi				# prevBodyY
mov (%esi, %edi, 4), %esi
mov %esi, (%edx)

inc %ecx						# sizeBody
cmp 8(%ebp), %ecx
JL loop			

exit:
pop %ebp
ret
 