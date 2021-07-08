
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
	Game(int gamelevel, int gameScore, int bonus);
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
	int minuten = 1;
	int sekunden1 = 3;
	int sekunden2 = 0;
	bool zeitAbgelaufen = false;
	int countBonusPoints = 0;
	int zufallszahlBonus = 1;
	int bonusPointX = 0;
	int bonusPointY = 0;
	bool bonusOnMap = false;

	bool MoveRight = false;
	bool MoveLeft = false;
	bool MoveUp = false;
	bool MoveDown = false;

	int geschwindigkeitLevel = 1;
	int geschwindigkeit = 2;
	int timeUpdate = 0;

	int level = 1;
	int counterWall = 0;
	int wallArray[999][2];

	bool stopAll = false;
	bool isRunning;
	SDL_Window* window;
};

#endif /* Game_h*/
