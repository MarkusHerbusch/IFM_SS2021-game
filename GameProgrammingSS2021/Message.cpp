#include "Message.h"
//#include "TextureManager.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>

SDL_Texture* textMessage1Tex;
SDL_Texture* textMessage2Tex;
SDL_Texture* textMessageLevelTex;
SDL_Texture* textMessage3Tex;
SDL_Texture* textMessageScoreTex;
SDL_Rect textMessage1R, textMessage2R, textMessageLevelR, textMessage3R, textMessageScoreR;

TTF_Font* fontMessage;
SDL_Color messageColor = { 0, 0, 0 };

SDL_Renderer* Message::renderer = nullptr;

Message::Message()
{}
Message::~Message()
{}

void Message::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int gamescore, int gamelevel, bool gametime)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	score = gamescore;
	level = gamelevel;
	time = gametime;



	if (TTF_Init() == -1)
	{
		std::cerr << "Konnte SDL_ttf nicht initialisieren! Fehler: " << TTF_GetError() << std::endl;
	}

	fontMessage = TTF_OpenFont("assets/arial.ttf", 60);
	if (!fontMessage)
	{
		std::cerr << "Konnte Schriftart nicht laden! Fehler: " << TTF_GetError() << std::endl;
	}


	if (time)
	{
	
		//Text1
		SDL_Surface* text1S = TTF_RenderText_Solid(fontMessage, "Drücke Enter zum Verlassen!", messageColor);
		textMessage1Tex = SDL_CreateTextureFromSurface(renderer, text1S);
		SDL_FreeSurface(text1S);
		int wText1 = 0;
		int hText1 = 0;
		TTF_SizeText(fontMessage, "Drücke Enter zum Verlassen!", &wText1, &hText1);
		textMessage1R.x = (800 - wText1) / 2;
		textMessage1R.y = 270;
		textMessage1R.w = wText1;
		textMessage1R.h = hText1;

		//Text2
		SDL_Surface* text2S = TTF_RenderText_Solid(fontMessage, "Zeit abgelaufen!", messageColor);
		textMessage2Tex = SDL_CreateTextureFromSurface(renderer, text2S);
		SDL_FreeSurface(text2S);
		int wText2 = 0;
		int hText2 = 0;
		TTF_SizeText(fontMessage, "Zeit abgelaufen!", &wText2, &hText2);
		textMessage2R.x = (800 - wText2) / 2;
		textMessage2R.y = 30;
		textMessage2R.w = wText2;
		textMessage2R.h = hText2;

		//Text3
		SDL_Surface* text3S = TTF_RenderText_Solid(fontMessage, "Dein erreichter Score:", messageColor);
		textMessage3Tex = SDL_CreateTextureFromSurface(renderer, text3S);
		SDL_FreeSurface(text3S);
		int wText3 = 0;
		int hText3 = 0;
		TTF_SizeText(fontMessage, "Dein erreichter Score:", &wText3, &hText3);
		textMessage3R.x = (800 - wText3) / 2 - 30;
		textMessage3R.y = 150;
		textMessage3R.w = wText3;
		textMessage3R.h = hText3;

		//Score
		std::string tmpScore = std::to_string(score);
		char const* score_char = tmpScore.c_str();
		SDL_Surface* numberScoreS = TTF_RenderText_Solid(fontMessage, score_char, messageColor);
		textMessageScoreTex = SDL_CreateTextureFromSurface(renderer, numberScoreS);
		SDL_FreeSurface(numberScoreS);
		int wNumberScore = 0;
		int hNumberScore = 0;
		TTF_SizeText(fontMessage, score_char, &wNumberScore, &hNumberScore);
		textMessageScoreR.x = 680;
		textMessageScoreR.y = 150;
		textMessageScoreR.w = wNumberScore;
		textMessageScoreR.h = hNumberScore;

	}
	else {

		//Text1
		SDL_Surface* text1S = TTF_RenderText_Solid(fontMessage, "Drücke Enter zum Fortsetzen!", messageColor);
		textMessage1Tex = SDL_CreateTextureFromSurface(renderer, text1S);
		SDL_FreeSurface(text1S);
		int wText1 = 0;
		int hText1 = 0;
		TTF_SizeText(fontMessage, "Drücke Enter zum Fortsetzen!", &wText1, &hText1);
		textMessage1R.x = (800 - wText1) / 2;
		textMessage1R.y = 270;
		textMessage1R.w = wText1;
		textMessage1R.h = hText1;

		if (level == 10)
		{
			//Text2
			SDL_Surface* text2S = TTF_RenderText_Solid(fontMessage, "Spiel abgeschlossen!", messageColor);
			textMessage2Tex = SDL_CreateTextureFromSurface(renderer, text2S);
			SDL_FreeSurface(text2S);
			int wText2 = 0;
			int hText2 = 0;
			TTF_SizeText(fontMessage, "Spiel abgeschlossen!", &wText2, &hText2);
			textMessage2R.x = (800 - wText2) / 2;
			textMessage2R.y = 30;
			textMessage2R.w = wText2;
			textMessage2R.h = hText2;

			//Text3
			SDL_Surface* text3S = TTF_RenderText_Solid(fontMessage, "Dein erreichter Score:", messageColor);
			textMessage3Tex = SDL_CreateTextureFromSurface(renderer, text3S);
			SDL_FreeSurface(text3S);
			int wText3 = 0;
			int hText3 = 0;
			TTF_SizeText(fontMessage, "Dein erreichter Score:", &wText3, &hText3);
			textMessage3R.x = (800 - wText3) / 2 - 30;
			textMessage3R.y = 150;
			textMessage3R.w = wText3;
			textMessage3R.h = hText3;

			//Score
			std::string tmpScore = std::to_string(score);
			char const* score_char = tmpScore.c_str();
			SDL_Surface* numberScoreS = TTF_RenderText_Solid(fontMessage, score_char, messageColor);
			textMessageScoreTex = SDL_CreateTextureFromSurface(renderer, numberScoreS);
			SDL_FreeSurface(numberScoreS);
			int wNumberScore = 0;
			int hNumberScore = 0;
			TTF_SizeText(fontMessage, score_char, &wNumberScore, &hNumberScore);
			textMessageScoreR.x = 680;
			textMessageScoreR.y = 150;
			textMessageScoreR.w = wNumberScore;
			textMessageScoreR.h = hNumberScore;
		}
		else {
			//Text2
			SDL_Surface* text2S = TTF_RenderText_Solid(fontMessage, "Level    abgeschlossen!", messageColor);
			textMessage2Tex = SDL_CreateTextureFromSurface(renderer, text2S);
			SDL_FreeSurface(text2S);
			int wText2 = 0;
			int hText2 = 0;
			TTF_SizeText(fontMessage, "Level    abgeschlossen!", &wText2, &hText2);
			textMessage2R.x = (800 - wText2) / 2;
			textMessage2R.y = 30;
			textMessage2R.w = wText2;
			textMessage2R.h = hText2;

			//Level
			std::string tmpLevel = std::to_string(level);
			char const* level_char = tmpLevel.c_str();
			SDL_Surface* numberTempoS = TTF_RenderText_Solid(fontMessage, level_char, messageColor);
			textMessageLevelTex = SDL_CreateTextureFromSurface(renderer, numberTempoS);
			SDL_FreeSurface(numberTempoS);
			int wNumberTempo = 0;
			int hNumberTempo = 0;
			TTF_SizeText(fontMessage, level_char, &wNumberTempo, &hNumberTempo);
			textMessageLevelR.x = 245;
			textMessageLevelR.y = 30;
			textMessageLevelR.w = wNumberTempo;
			textMessageLevelR.h = hNumberTempo;

			//Text3
			SDL_Surface* text3S = TTF_RenderText_Solid(fontMessage, "Dein aktueller Score:", messageColor);
			textMessage3Tex = SDL_CreateTextureFromSurface(renderer, text3S);
			SDL_FreeSurface(text3S);
			int wText3 = 0;
			int hText3 = 0;
			TTF_SizeText(fontMessage, "Dein aktueller Score:", &wText3, &hText3);
			textMessage3R.x = (800 - wText3) / 2 - 30;
			textMessage3R.y = 150;
			textMessage3R.w = wText3;
			textMessage3R.h = hText3;

			//Score
			std::string tmpScore = std::to_string(score);
			char const* score_char = tmpScore.c_str();
			SDL_Surface* numberScoreS = TTF_RenderText_Solid(fontMessage, score_char, messageColor);
			textMessageScoreTex = SDL_CreateTextureFromSurface(renderer, numberScoreS);
			SDL_FreeSurface(numberScoreS);
			int wNumberScore = 0;
			int hNumberScore = 0;
			TTF_SizeText(fontMessage, score_char, &wNumberScore, &hNumberScore);
			textMessageScoreR.x = 660;
			textMessageScoreR.y = 150;
			textMessageScoreR.w = wNumberScore;
			textMessageScoreR.h = hNumberScore;
		}
		
	}



}

void Message::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		//stopAll = true;
		break;


	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			//charakter = 1;
			isRunning = false;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void Message::render()
{
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	SDL_RenderCopy(renderer, textMessage1Tex, NULL, &textMessage1R);
	SDL_RenderCopy(renderer, textMessage2Tex, NULL, &textMessage2R);
	SDL_RenderCopy(renderer, textMessageLevelTex, NULL, &textMessageLevelR);
	SDL_RenderCopy(renderer, textMessage3Tex, NULL, &textMessage3R);
	SDL_RenderCopy(renderer, textMessageScoreTex, NULL, &textMessageScoreR);


	SDL_RenderPresent(renderer);
}

void Message::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Message Cleaned" << std::endl;

}