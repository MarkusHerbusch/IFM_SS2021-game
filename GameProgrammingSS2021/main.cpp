#include "Game.h"

Game* game = nullptr;

int main(int argc, const char* argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	int farbeSpieler;
	cout << "Welche Farbe soll dein Character haben?" << endl;
	cout << "1 - Blau" << endl;
	cout << "2 - Gelb" << endl;
	cout << "3 - Gruen" << endl;
	cout << "4 - Hellblau" << endl;
	cout << "5 - Pink" << endl;
	cout << "6 - Violett" << endl;
	cout << "7 - Weiss" << endl;

	cin >> farbeSpieler;


	game->init("Spiel", farbeSpieler, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}