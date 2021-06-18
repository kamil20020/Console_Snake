#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

extern "C" unsigned int keyService(unsigned int key, unsigned int direction);

extern "C" unsigned int ateItself(unsigned int sizeBody, unsigned int *bodyX, unsigned int *bodyY);

extern "C" unsigned int checkDoTouchWall(unsigned int direction, unsigned int headX, unsigned int headY, 
										 unsigned int fieldX, unsigned int fieldY, unsigned size);

extern "C" void updateHeadAfterMoveLogic(unsigned int direction, unsigned int &headX, unsigned int &headY, unsigned int speed);

extern "C" void updateBodyAfterMove(unsigned int sizeBody, unsigned int *bodyX, unsigned int *bodyY, 
									unsigned int *prevbodyX, unsigned int *prevbodyY);

extern "C" void updateTailAfterIncrease(unsigned int direction, unsigned int &lastBodyX, unsigned int &lastBodyY, 
												unsigned int prevLastBodyX, unsigned int prevLastBodyY);

extern "C" unsigned int updatePointsIfAteFood(unsigned int headX, unsigned int headY, unsigned int foodX, 
										unsigned int foodY, unsigned int &points, unsigned int snakeShapeSize, unsigned int foodShapeSize);

extern "C" unsigned int updatePoints(unsigned int &points, unsigned gained);

extern "C" unsigned int collider(unsigned int firstX, unsigned int firstY, unsigned int secondX, unsigned int secondY, unsigned int firstShapeSize, unsigned int secondShapeSize);

int fieldX = 600;
int fieldY = 600;

class Game{

	int sizeBody = 2;

	unsigned int* bodyX = new unsigned int[sizeBody];
	unsigned int* bodyY = new unsigned int[sizeBody];

	int foodX;
	int foodY;

	unsigned int points = 0;

	int direction = 4;

	int snakeShapeSize = 30;

	int foodShapeSize = 20;

public:

	void printSnake(SDL_Surface* snake, SDL_Surface *windowSurface){

		for(int i=0; i < sizeBody; i++){

			SDL_Rect snakePosition;

			snakePosition.x = bodyX[i];
			snakePosition.y = bodyY[i];

			SDL_BlitSurface(snake, NULL, windowSurface, &snakePosition );
		}
	}

	void printFood(SDL_Surface* food, SDL_Surface *windowSurface){

		SDL_Rect foodPosition;

		foodPosition.x = foodX;
		foodPosition.y = foodY;

		SDL_BlitSurface(food, NULL, windowSurface, &foodPosition );
	}

	void keyUse(int key) {

		direction = keyService(key, direction); 
	}

	void moving() {

		unsigned int *prevBodyX = new unsigned int[sizeBody];
		unsigned int *prevBodyY = new unsigned int[sizeBody];

		for (int i = 0; i < sizeBody; i++) {

			prevBodyX[i] = bodyX[i];
			prevBodyY[i] = bodyY[i];
		}

		updateHeadAfterMoveLogic(direction, bodyX[0], bodyY[0], snakeShapeSize);
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

			foodX = rand() % (fieldX - foodShapeSize);
			foodY = rand() % (fieldY - foodShapeSize);

			for (int i = 0; i < sizeBody; i++) {

				if(collider(bodyX[0], bodyY[0], foodX, foodY, snakeShapeSize, foodShapeSize) == 0);
					fieldIsClear = true;
			}

			if (fieldIsClear)
				break;
		}
	}

	bool checkDoLose(){

		if (checkDoTouchWall(direction, bodyX[0], bodyY[0], fieldX, fieldY, snakeShapeSize) == 1 || 
				ateItself(sizeBody, bodyX, bodyY) == 1)
			return true;

		return false;
	}

	bool checkDoWin(){

		if(sizeBody*snakeShapeSize*snakeShapeSize == fieldX*fieldY)
			return true;

		return false;
	}

	void eatingFoodLogic() {

		if(collider(bodyX[0], bodyY[0], foodX, foodY, snakeShapeSize, foodShapeSize) == 1){
			
			updatePoints(points, 1);
			incrementBody();
			spawnFood();
		}
	}

	void gameLoop(SDL_Surface *windowSurface, SDL_Window *window){

		const int frameRate  = 18;
		const int frameDelay = 1000 / frameRate;

		Uint32 frameTime;
		int frameElapsedTime;

		SDL_Surface *snake = IMG_Load("snake.png");
		SDL_Surface *food = IMG_Load("food.png");

		for(int i=0; i < sizeBody; i++){

			bodyX[i] = 300-i*snakeShapeSize;
			bodyY[i] = 300;
		}
		
		spawnFood();
		
		bool quit = false;
		SDL_Event event;
	 
		while (!quit){

			frameTime = SDL_GetTicks();

			while(SDL_PollEvent(&event)){
	 
				switch (event.type){

					case SDL_KEYDOWN:

						keyUse(event.key.keysym.sym);

						break;

					case SDL_QUIT:

						quit = true;

						break;
				}
			}

			moving();

			SDL_FillRect(windowSurface, NULL, 0x000000);	// czyszczenie ekranu

			printFood(food, windowSurface);

			printSnake(snake, windowSurface);
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
			
			frameElapsedTime = SDL_GetTicks() - frameTime;

			if (frameDelay > frameElapsedTime)
				SDL_Delay(frameDelay - frameElapsedTime);

			eatingFoodLogic();

			if(checkDoLose())
				break; 

		}

		SDL_FreeSurface( snake );
		SDL_FreeSurface( food );

		cout<< "Zdobyto: " << points << " punktow" <<endl;
	}

};

int main(){

	srand(time(0));

    SDL_Surface *windowSurface = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
 
    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, fieldX, fieldY, 0);
	windowSurface = SDL_GetWindowSurface( window );

	Game game;
	game.gameLoop(windowSurface, window);

	SDL_FreeSurface(windowSurface);

	SDL_Quit();
}
