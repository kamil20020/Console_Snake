.text

.global keyService

keyService:
push %ebp
mov %esp, %ebp

cmp $119, 8(%ebp)
JE WClicked

cmp $115, 8(%ebp)
JE SClicked

cmp $97, 8(%ebp)
JE AClicked

cmp $100, 8(%ebp)
JE DClicked

jmp default

WClicked:
cmp $2, 12(%ebp)
JE default
mov $1, %eax
jmp stack

SClicked:
cmp $1, 12(%ebp)
JE default
mov $2, %eax
jmp stack

AClicked:
cmp $4, 12(%ebp)
JE default
mov $3, %eax
jmp stack

DClicked:
cmp $3, 12(%ebp)
JE default
mov $4, %eax
jmp stack

default:
mov 12(%ebp), %eax

stack:
pop %ebp
ret
