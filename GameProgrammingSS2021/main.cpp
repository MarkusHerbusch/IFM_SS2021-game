#include "CharacterChoice.h"
#include "Game.h"
#include "Message.h"

CharacterChoice* characterChoice = nullptr;
Game* game = nullptr;
Message* message = nullptr;

struct ReturnCharacter {
	int chara;
	bool run;
};

struct ReturnGame {
	int score;
	bool run;
	int bonus;
	bool time;
};

int gamelevel = 1;
int score = 0;
int bonus = 0;


int main(int argc, const char* argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int farbeSpieler;
	bool stopAll;
	bool zeitAbgelaufen;

	

	struct ReturnCharacter ret;
	struct ReturnGame retGame;


	characterChoice = new CharacterChoice();
	characterChoice->init("Auswahl des Charakters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, false);
	while (characterChoice->running()) {

		characterChoice->handleEvents();
		characterChoice->render();
	}

	ret = characterChoice->clean();

	farbeSpieler = ret.chara;
	stopAll = ret.run;

	while (stopAll == false && gamelevel <= 10) {

		game = new Game(gamelevel, score, bonus);
		game->init("Spiel", farbeSpieler, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, false);

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

		retGame = game->clean();
		score = retGame.score;
		stopAll = retGame.run;
		bonus = retGame.bonus;
		zeitAbgelaufen = retGame.time;
		gamelevel++;

		if (stopAll == false || zeitAbgelaufen)
		{
			message = new Message();
			message->init("Message", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, false, score, gamelevel-1, zeitAbgelaufen);
			while (message->running()) {

				message->handleEvents();
				message->render();
			}
			message->clean();
		}


	}
	return 0;
}