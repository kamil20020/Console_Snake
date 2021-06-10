all: snake

snake: snake.cpp keyService.o ateItself.o checkDoTouchWall.o
	gcc -m32 ateItself.o keyService.o checkDoTouchWall.o snake.cpp -o snake -lstdc++ -lncurses

checkDoTouchWall: checkDoTouchWall.o
	ld checkDoTouchWall.o -m elf_i386 -o checkDoTouchWall

checkDoTouchWall.o: checkDoTouchWall.s
	as --32 checkDoTouchWall.s -g -o checkDoTouchWall.o

ateItself: ateItself.o
	ld ateItself.o -m elf_i386 -o ateItself

ateItself.o: ateItself.s
	as --32 ateItself.s -g -o ateItself.o

keyService: keyService.o
	ld keyService.o -m elf_i386 -o keyService

keyService.o: keyService.s
	as --32 keyService.s -g -o keyService.o

clean:
	rm snake