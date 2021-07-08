#include "CharacterChoice.h"
#include "TextureManager.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>

SDL_Texture* player1Tex;
SDL_Texture* player2Tex;
SDL_Texture* player3Tex;
SDL_Texture* player4Tex;
SDL_Texture* player5Tex;
SDL_Texture* player6Tex;
SDL_Texture* player7Tex;
SDL_Texture* text1Tex;
SDL_Texture* text2Tex;
SDL_Texture* number1Tex;
SDL_Texture* number2Tex;
SDL_Texture* number3Tex;
SDL_Texture* number4Tex;
SDL_Texture* number5Tex;
SDL_Texture* number6Tex;
SDL_Texture* number7Tex;

SDL_Rect player1R;
SDL_Rect player2R;
SDL_Rect player3R;
SDL_Rect player4R;
SDL_Rect player5R;
SDL_Rect player6R;
SDL_Rect player7R;
SDL_Rect text1R, text2R;
SDL_Rect number1R, number2R, number3R, number4R, number5R, number6R, number7R;

TTF_Font* fontCharakterChoice;
SDL_Color blackColor = { 0, 0, 0 };

struct ReturnCharacter {
	int chara;
	bool run;
};

SDL_Renderer* CharacterChoice::renderer = nullptr;

CharacterChoice::CharacterChoice()
{}
CharacterChoice::~CharacterChoice()
{}

void CharacterChoice::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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

	//Blau
	SDL_Surface* tmpSurface1 = NULL;
	tmpSurface1 = IMG_Load("images/SpielerBlau.png");
	player1Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface1);
	SDL_FreeSurface(tmpSurface1);
	player1R.x = 68;
	player1R.y = 325;
	player1R.h = 150;
	player1R.w = 150;

	//Gelb
	SDL_Surface* tmpSurface2 = NULL;
	tmpSurface2 = IMG_Load("images/SpielerGelb.png");
	player2Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface2);
	SDL_FreeSurface(tmpSurface2);
	player2R.x = 286;
	player2R.y = 325;
	player2R.h = 150;
	player2R.w = 150;

	//Gruen
	SDL_Surface* tmpSurface3 = NULL;
	tmpSurface3 = IMG_Load("images/SpielerGruen.png");
	player3Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface3);
	SDL_FreeSurface(tmpSurface3);
	player3R.x = 504;
	player3R.y = 325;
	player3R.h = 150;
	player3R.w = 150;

	//Hellblau
	SDL_Surface* tmpSurface4 = NULL;
	tmpSurface4 = IMG_Load("images/SpielerHellblau.png");
	player4Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface4);
	SDL_FreeSurface(tmpSurface4);
	player4R.x = 722;
	player4R.y = 325;
	player4R.h = 150;
	player4R.w = 150;

	//Pink
	SDL_Surface* tmpSurface5 = NULL;
	tmpSurface5 = IMG_Load("images/SpielerPink.png");
	player5Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface5);
	SDL_FreeSurface(tmpSurface5);
	player5R.x = 940;
	player5R.y = 325;
	player5R.h = 150;
	player5R.w = 150;

	//Violett
	SDL_Surface* tmpSurface6 = NULL;
	tmpSurface6 = IMG_Load("images/SpielerViolett.png");
	player6Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface6);
	SDL_FreeSurface(tmpSurface6);
	player6R.x = 1158;
	player6R.y = 325;
	player6R.h = 150;
	player6R.w = 150;

	//Weiss
	SDL_Surface* tmpSurface7 = NULL;
	tmpSurface7 = IMG_Load("images/SpielerWeiss.png");
	player7Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface7);
	SDL_FreeSurface(tmpSurface7);
	player7R.x = 1376;
	player7R.y = 325;
	player7R.h = 150;
	player7R.w = 150;


	if (TTF_Init() == -1)
	{
		std::cerr << "Konnte SDL_ttf nicht initialisieren! Fehler: " << TTF_GetError() << std::endl;
	}

	fontCharakterChoice = TTF_OpenFont("assets/arial.ttf", 60);
	if (!fontCharakterChoice)
	{
		std::cerr << "Konnte Schriftart nicht laden! Fehler: " << TTF_GetError() << std::endl;
	}

	//Text1
	SDL_Surface* text1S = TTF_RenderText_Solid(fontCharakterChoice, "Wähle deinen Charakter für das Spiel aus!", blackColor);
	text1Tex = SDL_CreateTextureFromSurface(renderer, text1S);
	SDL_FreeSurface(text1S);
	int wText1 = 0;
	int hText1 = 0;
	TTF_SizeText(fontCharakterChoice, "Wähle deinen Charakter für das Spiel aus!", &wText1, &hText1);
	text1R.x = (1600 - wText1) / 2;
	text1R.y = 30;
	text1R.w = wText1;
	text1R.h = hText1;

	//Text2
	SDL_Surface* text2S = TTF_RenderText_Solid(fontCharakterChoice, "Drücke dafür die entsprechende Nummer.", blackColor);
	text2Tex = SDL_CreateTextureFromSurface(renderer, text2S);
	SDL_FreeSurface(text2S);
	int wText2 = 0;
	int hText2 = 0;
	TTF_SizeText(fontCharakterChoice, "Drücke dafür die entsprechende Nummer.", &wText2, &hText2);
	text2R.x = (1600 - wText2) / 2;
	text2R.y = 110;
	text2R.w = wText2;
	text2R.h = hText2;

	//Number1
	SDL_Surface* number1S = TTF_RenderText_Solid(fontCharakterChoice, "1", blackColor);
	number1Tex = SDL_CreateTextureFromSurface(renderer, number1S);
	SDL_FreeSurface(number1S);
	int wnumber1 = 0;
	int hnumber1 = 0;
	TTF_SizeText(fontCharakterChoice, "1", &wnumber1, &hnumber1);
	number1R.x = (150 - wnumber1) /2 + 68;
	number1R.y = 500;
	number1R.w = wnumber1;
	number1R.h = hnumber1;

	//Number2
	SDL_Surface* number2S = TTF_RenderText_Solid(fontCharakterChoice, "2", blackColor);
	number2Tex = SDL_CreateTextureFromSurface(renderer, number2S);
	SDL_FreeSurface(number2S);
	int wnumber2 = 0;
	int hnumber2 = 0;
	TTF_SizeText(fontCharakterChoice, "2", &wnumber2, &hnumber2);
	number2R.x = (150 - wnumber2) / 2 + 286;
	number2R.y = 500;
	number2R.w = wnumber2;
	number2R.h = hnumber2;

	//Number3
	SDL_Surface* number3S = TTF_RenderText_Solid(fontCharakterChoice, "3", blackColor);
	number3Tex = SDL_CreateTextureFromSurface(renderer, number3S);
	SDL_FreeSurface(number3S);
	int wnumber3 = 0;
	int hnumber3 = 0;
	TTF_SizeText(fontCharakterChoice, "3", &wnumber3, &hnumber3);
	number3R.x = (150 - wnumber3) / 2 + 504;
	number3R.y = 500;
	number3R.w = wnumber3;
	number3R.h = hnumber3;

	//Number4
	SDL_Surface* number4S = TTF_RenderText_Solid(fontCharakterChoice, "4", blackColor);
	number4Tex = SDL_CreateTextureFromSurface(renderer, number4S);
	SDL_FreeSurface(number4S);
	int wnumber4 = 0;
	int hnumber4 = 0;
	TTF_SizeText(fontCharakterChoice, "4", &wnumber4, &hnumber4);
	number4R.x = (150 - wnumber4) / 2 + 722;
	number4R.y = 500;
	number4R.w = wnumber4;
	number4R.h = hnumber4;

	//Number5
	SDL_Surface* number5S = TTF_RenderText_Solid(fontCharakterChoice, "5", blackColor);
	number5Tex = SDL_CreateTextureFromSurface(renderer, number5S);
	SDL_FreeSurface(number5S);
	int wnumber5 = 0;
	int hnumber5 = 0;
	TTF_SizeText(fontCharakterChoice, "5", &wnumber5, &hnumber5);
	number5R.x = (150 - wnumber5) / 2 + 940;
	number5R.y = 500;
	number5R.w = wnumber5;
	number5R.h = hnumber5;

	//Number6
	SDL_Surface* number6S = TTF_RenderText_Solid(fontCharakterChoice, "6", blackColor);
	number6Tex = SDL_CreateTextureFromSurface(renderer, number6S);
	SDL_FreeSurface(number6S);
	int wnumber6 = 0;
	int hnumber6 = 0;
	TTF_SizeText(fontCharakterChoice, "6", &wnumber6, &hnumber6);
	number6R.x = (150 - wnumber6) / 2 + 1158;
	number6R.y = 500;
	number6R.w = wnumber6;
	number6R.h = hnumber6;

	//Number7
	SDL_Surface* number7S = TTF_RenderText_Solid(fontCharakterChoice, "7", blackColor);
	number7Tex = SDL_CreateTextureFromSurface(renderer, number7S);
	SDL_FreeSurface(number7S);
	int wnumber7 = 0;
	int hnumber7 = 0;
	TTF_SizeText(fontCharakterChoice, "7", &wnumber7, &hnumber7);
	number7R.x = (150 - wnumber7) / 2 + 1376;
	number7R.y = 500;
	number7R.w = wnumber7;
	number7R.h = hnumber7;

}


void CharacterChoice::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		stopAll = true;
		break;


	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_1:
			charakter = 1;
			isRunning = false;
			break;

		case SDLK_2:
			charakter = 2;
			isRunning = false;
			break;

		case SDLK_3:
			charakter = 3;
			isRunning = false;
			break;

		case SDLK_4:
			charakter = 4;
			isRunning = false;
			break;

		case SDLK_5:
			charakter = 5;
			isRunning = false;
			break;

		case SDLK_6:
			charakter = 6;
			isRunning = false;
			break;

		case SDLK_7:
			charakter = 7;
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

void CharacterChoice::render()
{
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	SDL_RenderCopy(renderer, player1Tex, NULL, &player1R);
	SDL_RenderCopy(renderer, player2Tex, NULL, &player2R);
	SDL_RenderCopy(renderer, player3Tex, NULL, &player3R);
	SDL_RenderCopy(renderer, player4Tex, NULL, &player4R);
	SDL_RenderCopy(renderer, player5Tex, NULL, &player5R);
	SDL_RenderCopy(renderer, player6Tex, NULL, &player6R);
	SDL_RenderCopy(renderer, player7Tex, NULL, &player7R);
	SDL_RenderCopy(renderer, text1Tex, NULL, &text1R);
	SDL_RenderCopy(renderer, text2Tex, NULL, &text2R);
	SDL_RenderCopy(renderer, number1Tex, NULL, &number1R);
	SDL_RenderCopy(renderer, number2Tex, NULL, &number2R);
	SDL_RenderCopy(renderer, number3Tex, NULL, &number3R);
	SDL_RenderCopy(renderer, number4Tex, NULL, &number4R);
	SDL_RenderCopy(renderer, number5Tex, NULL, &number5R);
	SDL_RenderCopy(renderer, number6Tex, NULL, &number6R);
	SDL_RenderCopy(renderer, number7Tex, NULL, &number7R);

	SDL_RenderPresent(renderer);
}

struct ReturnCharacter CharacterChoice::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "CharacterChoice Cleaned" << std::endl;

	struct ReturnCharacter ret;
	ret.chara = charakter;
	ret.run = stopAll;

	return ret;
}