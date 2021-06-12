#include <iostream>
#include <unistd.h>	// sleep
#include <ncurses.h>

extern "C" unsigned int keyService(unsigned int key, unsigned int direction);

extern "C" unsigned int ateItself(unsigned int sizeBody, unsigned int *bodyX, unsigned int *bodyY);

extern "C" unsigned int checkDoTouchWall(unsigned int direction, unsigned int headX, unsigned int headY, 
										 unsigned int fieldX, unsigned int fieldY);

extern "C" unsigned int moveLogic(unsigned int direction, unsigned int *bodyX, unsigned int *bodyY, 
								  unsigned int fieldX, unsigned int fieldY, unsigned int sizeBody, 
								  unsigned int *prevBodyX, unsigned int *prevBodyY);

extern "C" unsigned int updateHeadAfterMoveLogic(unsigned int direction, unsigned int *bodyX, unsigned int *bodyY, 
												 unsigned int fieldX, unsigned int fieldY);


int value = 0;

using namespace std;

unsigned int* bodyX = new unsigned int[5];
unsigned int* bodyY = new unsigned int[5];

int sizeBody = 5;

int fieldX = 50;
int fieldY = 20;

int foodX = 30;
int foodY = 15;

int points = 0;

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

    for (int j = 1; j < fieldX; j++) {

        printw("#");
    }

    printw("\n");

    for (int i = 0; i < fieldY; i++) {

        printw("#");

        for (int j = 1; j < fieldX-2; j++) {

            printw(" ");
        }

        printw("#\n");
    }

    for (int j = 1; j < fieldX; j++) {

        printw("#");
    }
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
	
	while(sign != 32){

		sign = getch();
	}

	clear();
}

void keyUse() {

	direction = keyService(getch(), direction); 
}

void setPreviousPosition(unsigned int *prevBodyX, unsigned int *prevBodyY) {

    for (int i = 1; i < sizeBody; i++) {

        bodyX[i] = prevBodyX[i - 1];
        bodyY[i] = prevBodyY[i - 1];
    }
}

void moving() {

    unsigned int *prevBodyX = new unsigned int[sizeBody]; // dynamiczne, gdyz nie wiedzialem jak zrobic zwykla tablice o rozmiarze rownym zmiennej
    unsigned int *prevBodyY = new unsigned int[sizeBody];

    for (int i = 0; i < sizeBody; i++) {

        prevBodyX[i] = bodyX[i];
        prevBodyY[i] = bodyY[i];
    }

	if(updateHeadAfterMoveLogic(direction, bodyX, bodyY, fieldX, fieldY) == 1)
		setPreviousPosition(prevBodyX, prevBodyY);

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

    switch (direction) {

        case 1:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2];
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2] + 1;

            break;

        case 2:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2];
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2] - 1;

            break;

        case 3:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2] + 1;
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2];

            break;

        case 4:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2] - 1;
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2];

            break;
    }
}

void spawnFood(){

	while (true) {

		bool fieldIsClear = false;

		foodX = rand() % fieldX - 3 + 1;
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

void eatingFoodLogic() {

    if (bodyX[0] == foodX && bodyY[0] == foodY) {

        incrementBody();

		spawnFood();

        points++;
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

        if (checkDoTouchWall(direction, bodyX[0], bodyY[0], fieldX, fieldY) == 1 || 
			ateItself(sizeBody, bodyX, bodyY) == 1){

			break;
		}
        eatingFoodLogic();

        drawFood();
        drawSnake();
        drawPoints(55, 10);
		refresh();
    }

	endwin(); // end ncurses

	cout<< value;
}

