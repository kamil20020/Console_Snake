.text

.global keyService

keyService:
push %ebp
mov %esp, %ebp

cmpl $119, 8(%ebp)
JE WClicked

cmpl $115, 8(%ebp)
JE SClicked

cmpl $97, 8(%ebp)
JE AClicked

cmpl $100, 8(%ebp)
JE DClicked

jmp default

WClicked:
cmp $2, 12(%ebp)
JE stack
mov $1, %eax
jmp stack

SClicked:
cmp $1, 12(%ebp)
JE stack
mov $2, %eax
jmp stack

AClicked:
cmp $4, 12(%ebp)
JE stack
mov $3, %eax
jmp stack

DClicked:
cmp $3, 12(%ebp)
JE stack
mov $4, %eax
jmp stack

default:
mov 12(%ebp), %eax

stack:
pop %ebp
ret
