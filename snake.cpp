#include <iostream>
#include <unistd.h>	// sleep
#include <ncurses.h>

extern "C" unsigned int keyService(unsigned int key, unsigned int direction);

extern "C" unsigned int ateItself(unsigned int sizeBody, unsigned int *bodyX, unsigned int *bodyY);

extern "C" unsigned int checkDoTouchWall(unsigned int direction, unsigned int headX, unsigned int headY, 
										 unsigned int fieldX, unsigned int fieldY);

extern "C" void updateHeadAfterMoveLogic(unsigned int direction, unsigned int &headX, unsigned int &headY);

extern "C" void updateBodyAfterMove(unsigned int sizeBody, unsigned int *bodyX, unsigned int *bodyY, 
									unsigned int *prevbodyX, unsigned int *prevbodyY);

extern "C" void updateTailAfterIncrease(unsigned int direction, unsigned int &lastBodyX, unsigned int &lastBodyY, 
												unsigned int prevLastBodyX, unsigned int prevLastBodyY);

extern "C" unsigned int updatePointsIfAteFood(unsigned int headX, unsigned int headY, unsigned int foodX, 
										unsigned int foodY, unsigned int &points);


using namespace std;

unsigned int* bodyX = new unsigned int[5];
unsigned int* bodyY = new unsigned int[5];

int sizeBody = 5;

int fieldX = 50;
int fieldY = 20;

int foodX = 30;
int foodY = 15;

unsigned int points = 0;

int direction = 4;

void gotoxy(int x, int y) { // ustawienie pozycji kursora (kreska w konsoli)

    move(y, x);
	refresh();
}

void clearSnake() {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        printw(" ");
    }
}

void drawFrame() {

    for (int j = 0; j < fieldX+2; j++) 
        printw("#");

    printw("\n");

    for (int i = 0; i < fieldY; i++) {

        printw("#");

        for (int j = 0; j < fieldX; j++) 
            printw(" ");

        printw("#\n");
    }

    for (int j = 0; j < fieldX+2; j++) 
        printw("#");
}

void drawSnake() {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        printw("o");
    }
}

void drawFood() {

    gotoxy(foodX, foodY);
    printw("$");
}

void drawPoints(int x, int y) {

    gotoxy(x, y);
    printw("Punkty: %d", points);
}

void welcomeMessage(){

	gotoxy(10, 200);
	printw("Nacisnij klawisz SPACE aby rozpoczac rozgrywke");

	int sign = -1;

	while(sign != 32)
		sign = getch();

	clear();
}

void keyUse() {

	direction = keyService(getch(), direction); 
}

void moving() {

    unsigned int *prevBodyX = new unsigned int[sizeBody];
    unsigned int *prevBodyY = new unsigned int[sizeBody];

    for (int i = 0; i < sizeBody; i++) {

        prevBodyX[i] = bodyX[i];
        prevBodyY[i] = bodyY[i];
    }

	updateHeadAfterMoveLogic(direction, bodyX[0], bodyY[0]);
	updateBodyAfterMove(sizeBody, bodyX, bodyY, prevBodyX, prevBodyY);

    delete [] prevBodyX;
    delete [] prevBodyY;
}

void incrementBody() {

    sizeBody++;

    unsigned int* newBodyX = new unsigned int[sizeBody];
    unsigned int* newBodyY = new unsigned int[sizeBody];

    for (int i = 0; i < sizeBody - 1; i++) {

        newBodyX[i] = bodyX[i];
        newBodyY[i] = bodyY[i];
    }

    newBodyX[sizeBody - 1] = 0;
    newBodyY[sizeBody - 1] = 0;

    delete[] bodyX;
    delete[] bodyY;

    bodyX = newBodyX;
    bodyY = newBodyY;

    updateTailAfterIncrease(direction, newBodyX[sizeBody - 1], newBodyY[sizeBody - 1], newBodyX[sizeBody - 2], newBodyY[sizeBody - 2]);
}

void spawnFood(){

	while (true) {

		bool fieldIsClear = false;

		foodX = rand() % fieldX + 1;
		foodY = rand() % fieldY + 1;

		for (int i = 0; i < sizeBody; i++) {

			if (bodyX[i] == foodX && bodyY[i] == foodY) {

				fieldIsClear = false;
				break;
			}
			else
				fieldIsClear = true;
		}

		if (fieldIsClear)
			break;
	}
}

bool checkDoLose(){

	if (checkDoTouchWall(direction, bodyX[0], bodyY[0], fieldX, fieldY) == 1 || 
			ateItself(sizeBody, bodyX, bodyY) == 1)
		return true;

	return false;
}

bool checkDoWin(){

	return false;
}

void eatingFoodLogic() {

	if(updatePointsIfAteFood(bodyX[0], bodyY[0], foodX, foodY, points) == 1){

		incrementBody();
		spawnFood();
	}
}

int main(){

	for(int i=0; i < sizeBody; i++){

		bodyX[i] = 10-i;
		bodyY[i] = 10;
	}

	initscr(); // initialize ncurses
	//raw();     // CTRL-Z dont end program etc.
    noecho();  // pressed symbols wont be printed to screen
	nodelay(stdscr, TRUE); // without waiting for getch
	curs_set(0); //hide cursor

	welcomeMessage();

    drawFrame();
    drawSnake();
    drawFood();
    drawPoints(55, 10);
	refresh();

	usleep(1000000);

    while (true) {

		usleep(100000); //funkcja dla mikrosekund
		clearSnake();
        keyUse();
        moving();

        if(checkDoLose())
			break; 

        eatingFoodLogic();
        drawFood();
        drawSnake();
        drawPoints(55, 10);
		refresh();
    }

	endwin(); // end ncurses
}
