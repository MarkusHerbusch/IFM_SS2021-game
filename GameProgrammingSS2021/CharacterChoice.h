
#ifndef CharacterChoice_h
#define CharacterChoice_h

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class CharacterChoice {

public:
	CharacterChoice();
	~CharacterChoice();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	//void update();
	void render();
	struct ReturnCharacter clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;


private:
	//int cnt = 0; //zum Anzeigen auf der Konsole

	int charakter = 0;
	bool stopAll = false;

	bool isRunning;
	SDL_Window* window;
};

#endif /* CharacterChoice_h*/
