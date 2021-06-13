all: snake

snake: snake.cpp keyService.o ateItself.o checkDoTouchWall.o updateHeadAfterMoveLogic.o updateBodyAfterMove.o updateTailAfterIncrease.o updatePointsIfAteFood.o
	   gcc -m32 ateItself.o keyService.o checkDoTouchWall.o updateHeadAfterMoveLogic.o updateBodyAfterMove.o updateTailAfterIncrease.o updatePointsIfAteFood.o snake.cpp -o snake -lstdc++ -lncurses

updatePointsIfAteFood: updatePointsIfAteFood.o
	ld updatePointsIfAteFood.o -m elf_i386 -o updatePointsIfAteFood

updatePointsIfAteFood.o: updatePointsIfAteFood.s
	as --32 updatePointsIfAteFood.s -g -o updatePointsIfAteFood.o

updateTailAfterIncrease: updateTailAfterIncrease.o
	ld updateTailAfterIncrease.o -m elf_i386 -o updateTailAfterIncrease

updateTailAfterIncrease.o: updateTailAfterIncrease.s
	as --32 updateTailAfterIncrease.s -g -o updateTailAfterIncrease.o

updateBodyAfterMove: updateBodyAfterMove.o
	ld updateBodyAfterMove.o -m elf_i386 -o updateBodyAfterMove

updateBodyAfterMove.o: updateBodyAfterMove.s
	as --32 updateBodyAfterMove.s -g -o updateBodyAfterMove.o

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