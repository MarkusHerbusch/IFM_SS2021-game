
#ifndef Game_h
#define Game_h

#define SDL_MAIN_HANDLED
#include "SDL.h""
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int farbeSpieler, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;


private:
	int cnt = 0; //zum Anzeigen auf der Konsole
	int x = 200;
	int y = 200;

	bool MoveRight = false;
	bool MoveLeft = false;
	bool MoveUp = false;
	bool MoveDown = false;

	int geschwindigkeit = 2;

	bool isRunning;
	SDL_Window* window;
};

#endif /* Game_h*/
