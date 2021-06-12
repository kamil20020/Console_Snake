all: snake

snake: snake.cpp keyService.o ateItself.o checkDoTouchWall.o updateHeadAfterMoveLogic.o
	   gcc -m32 ateItself.o keyService.o checkDoTouchWall.o updateHeadAfterMoveLogic.o snake.cpp -o snake -lstdc++ -lncurses

updateHeadAfterMoveLogic: updateHeadAfterMoveLogic.o
	ld updateHeadAfterMoveLogic.o -m elf_i386 -o updateHeadAfterMoveLogic

updateHeadAfterMoveLogic.o: updateHeadAfterMoveLogic.s
	as --32 updateHeadAfterMoveLogic.s -g -o updateHeadAfterMoveLogic.o

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