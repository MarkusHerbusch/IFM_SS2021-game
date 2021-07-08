#ifndef Message_h
#define Message_h

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Message {

public:
	Message();
	~Message();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int gamescore, int gamelevel, bool time);

	void handleEvents();
	//void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;


private:
	
	int level = 0;
	int score = 0;
	bool time = false;
	//bool stopAll = false;

	bool isRunning;
	SDL_Window* window;
};

#endif /* Message_h*/