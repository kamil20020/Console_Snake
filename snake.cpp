#include <iostream>
#include <unistd.h>	// sleep
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
										unsigned int foodY, unsigned int &points, unsigned int snakeSize, unsigned int foodSize);

extern "C" unsigned int updatePoints(unsigned int &points, unsigned gained);

extern "C" unsigned int collider(unsigned int firstX, unsigned int firstY, unsigned int secondX, unsigned int secondY, unsigned int firstSize, unsigned int secondSize);


using namespace std;

unsigned int* bodyX = new unsigned int[5];
unsigned int* bodyY = new unsigned int[5];

int sizeBody = 5;

int fieldX = 600;
int fieldY = 400;

int foodX = 30;
int foodY = 15;

unsigned int points = 0;

int direction = 4;

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

	updateHeadAfterMoveLogic(direction, bodyX[0], bodyY[0], 10);
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

		foodX = rand() % (fieldX - 20);
		foodY = rand() % (fieldY - 20);

		for (int i = 0; i < sizeBody; i++) {

			if(bodyX[i] + 30 > foodX && bodyX[i] < foodX + 20){

				if(bodyY[i] + 30 > foodY && bodyY[i] < foodY + 20){
					
					fieldIsClear = false;
					break;
				}
			}

			fieldIsClear = true;
		}

		if (fieldIsClear)
			break;
	}
}

bool checkDoLose(){

	if (checkDoTouchWall(direction, bodyX[0], bodyY[0], fieldX, fieldY, 30) == 1 || 
			ateItself(sizeBody, bodyX, bodyY) == 1)
		return true;

	return false;
}

bool checkDoWin(){

	return false;
}

void eatingFoodLogic() {

	if(collider(bodyX[0], bodyY[0], foodX, foodY, 30, 20) == 1){
		
		updatePoints(points, 1);
		incrementBody();
		spawnFood();
	}
}

int main(){

	srand(time(0));

	for(int i=0; i < sizeBody; i++){

		bodyX[i] = 100-i*10;
		bodyY[i] = 100;
	}
	
	spawnFood();

	usleep(1000000);

	SDL_Surface *snake = NULL;
	SDL_Surface *food = NULL;
    SDL_Surface *windowSurface = NULL;
 
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){

        cout << "SDL could not initialize! SDL Error: " << SDL_GetError( ) <<endl;
    }
 
    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
	windowSurface = SDL_GetWindowSurface( window );

	if ( NULL == window ){

        cout << "Could not create window: " << SDL_GetError( ) << endl;
        
        return EXIT_FAILURE;
    }

	snake = IMG_Load("snake.png");
	food = IMG_Load("food.png");

    if( snake == NULL ){

        std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;
    }
	
	bool quit = false;
    SDL_Event event;
 
    while (!quit){

		usleep(50000); //funkcja dla mikrosekund

		SDL_PollEvent(&event);

		keyUse(event.key.keysym.sym);
 
        switch (event.type){

            case SDL_QUIT:

                quit = true;

                break;
        }

		eatingFoodLogic();

		if(checkDoLose())
			break; 

		moving();

		cout<< bodyX[0] << "\t" << foodX <<endl<<endl;
		cout<< bodyY[0] << "\t" << foodY <<endl;

		SDL_FillRect(windowSurface, NULL, 0x000000);	// czyszczenie ekranu

		SDL_Rect foodPosition;

		foodPosition.x = foodX;
		foodPosition.y = foodY;

		SDL_BlitSurface(food, NULL, windowSurface, &foodPosition );

		for(int i=0; i < sizeBody; i++){

			SDL_Rect snakePosition;

			snakePosition.x = bodyX[i];
			snakePosition.y = bodyY[i];

			SDL_BlitSurface(snake, NULL, windowSurface, &snakePosition );
		}
        
        //Update the surface
        SDL_UpdateWindowSurface( window );
    }

	SDL_FreeSurface( snake );
    SDL_FreeSurface( windowSurface );

	SDL_Quit();
}
