all: snake

snake: snake.cpp keyService.o
	gcc -m32 keyService.o snake.cpp -o snake -lstdc++ -lncurses

keyService: keyService.o
	ld keyService.o -m elf_i386 -o keyService

keyService.o: keyService.s
	as --32 keyService.s -g -o keyService.o

clean:
	rm snake