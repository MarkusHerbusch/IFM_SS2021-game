
#ifndef Game_h
#define Game_h

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Game {

public:
	Game(int gamelevel, int gameScore);
	~Game();

	void init(const char* title, int farbeSpieler, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	struct ReturnGame clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;


private:
	int cnt = 0; //zum Anzeigen auf der Konsole
	int x = 200;
	int y = 200;

	int points[10][2];
	int arrayFuellmenge = 0;
	int counterPoints = 0;
	int levelMaxPoints = 15;
	int score = 0;
	int scoreLevel = 0;
	int minuten = 2;
	int sekunden1 = 0;
	int sekunden2 = 0;
	bool zeitAbgelaufen = false;

	bool MoveRight = false;
	bool MoveLeft = false;
	bool MoveUp = false;
	bool MoveDown = false;

	bool geschwindigkeitPress = false;
	int geschwindigkeit = 2;

	int level = 1;
	int counterWall = 0;
	int wallArray[999][2];

	bool stopAll = false;
	bool isRunning;
	SDL_Window* window;
};

#endif /* Game_h*/
