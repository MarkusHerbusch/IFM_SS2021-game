#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>

SDL_Texture* playerTex;
SDL_Texture* textScoreTex;
SDL_Texture* scoreTex;
SDL_Texture* timeMinutesTex;
SDL_Texture* timeSeconds1Tex;
SDL_Texture* timeSeconds2Tex;
SDL_Texture* timePointTex;
SDL_Rect scrR, destR;
SDL_Rect textScoreR;
SDL_Rect scoreR;
SDL_Rect timeMinutesR, timeSeconds1R, timeSeconds2R, timePointR;
TTF_Font* font42;
SDL_Color yellow = { 255, 255, 0 };
SDL_Color black = { 0, 0, 0 };
SDL_Color colorTime = { 0, 255, 0 };


struct IntPair {
	int first, second;
};

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(int gamelevel)
{
	level = gamelevel;
}
Game::~Game()
{}

void Game::init(const char* title, int farbeSpieler, int xpos, int ypos, int width, int height, bool fullscreen)
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

	SDL_Surface* tmpSurface = NULL;

	if (farbeSpieler == 1) 
	{
		tmpSurface = IMG_Load("images/SpielerBlau.png");
	}
	else if (farbeSpieler == 2)
	{
		tmpSurface = IMG_Load("images/SpielerGelb.png");
	}
	else if (farbeSpieler == 3)
	{
		tmpSurface = IMG_Load("images/SpielerGruen.png");
	}
	else if (farbeSpieler == 4)
	{
		tmpSurface = IMG_Load("images/SpielerHellblau.png");
	}
	else if (farbeSpieler == 5)
	{
		tmpSurface = IMG_Load("images/SpielerPink.png");
	}
	else if (farbeSpieler == 6)
	{
		tmpSurface = IMG_Load("images/SpielerViolett.png");
	}
	else if (farbeSpieler == 7)
	{
		tmpSurface = IMG_Load("images/SpielerWeiss.png");
	}

	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	map = new Map(level);
	destR.x = 200;
	destR.y = 200;



	if (TTF_Init() == -1)
	{
		std::cerr << "Konnte SDL_ttf nicht initialisieren! Fehler: " << TTF_GetError() << std::endl;
	}

	font42 = TTF_OpenFont("assets/arial.ttf", 42);
	if (!font42)
	{
		std::cerr << "Konnte Schriftart nicht laden! Fehler: " << TTF_GetError() << std::endl;
	}

	//Anzeige Text Score
	SDL_Surface* textScoreS = TTF_RenderText_Solid(font42, "Score:", yellow);
	textScoreTex = SDL_CreateTextureFromSurface(renderer, textScoreS);
	SDL_FreeSurface(textScoreS);

	int wTextScore = 0;
	int hTextScore = 0;
	TTF_SizeText(font42, "Score:", &wTextScore, &hTextScore);
	std::cout << "Width : " << wTextScore << "\nHeight: " << hTextScore << std::endl;
	textScoreR.x = 1350;
	textScoreR.y = 10;
	textScoreR.w = wTextScore;
	textScoreR.h = hTextScore;

	//Anzeige Score
	SDL_Surface* scoreS = TTF_RenderText_Solid(font42, "0", yellow);
	scoreTex = SDL_CreateTextureFromSurface(renderer, scoreS);
	SDL_FreeSurface(scoreS);

	int wScore = 0;
	int hScore = 0;
	TTF_SizeText(font42, "0", &wScore, &hScore);
	std::cout << "Width : " << wScore << "\nHeight: " << hScore << std::endl;
	scoreR.x = 1480;
	scoreR.y = 10;
	scoreR.w = wScore;
	scoreR.h = hScore;

	//Anzeige Minuten
	SDL_Surface* timeMinutesS = TTF_RenderText_Solid(font42, "2", colorTime);
	timeMinutesTex = SDL_CreateTextureFromSurface(renderer, timeMinutesS);
	SDL_FreeSurface(timeMinutesS);

	int wMinutes = 0;
	int hMinutes = 0;
	TTF_SizeText(font42, "2", &wMinutes, &hMinutes);
	std::cout << "Width : " << wMinutes << "\nHeight: " << hMinutes << std::endl;
	timeMinutesR.x = 800;
	timeMinutesR.y = 10;
	timeMinutesR.w = wMinutes;
	timeMinutesR.h = hMinutes;

	//Anzeige Sekunden1
	SDL_Surface* timeSeconds1S = TTF_RenderText_Solid(font42, "0", colorTime);
	timeSeconds1Tex = SDL_CreateTextureFromSurface(renderer, timeSeconds1S);
	SDL_FreeSurface(timeSeconds1S);

	int wSeconds1 = 0;
	int hSeconds1 = 0;
	TTF_SizeText(font42, "0", &wSeconds1, &hSeconds1);
	timeSeconds1R.x = 850;
	timeSeconds1R.y = 10;
	timeSeconds1R.w = wSeconds1;
	timeSeconds1R.h = hSeconds1;

	//Anzeige Sekunden2
	SDL_Surface* timeSeconds2S = TTF_RenderText_Solid(font42, "0", colorTime);
	timeSeconds2Tex = SDL_CreateTextureFromSurface(renderer, timeSeconds2S);
	SDL_FreeSurface(timeSeconds2S);

	int wSeconds2 = 0;
	int hSeconds2 = 0;
	TTF_SizeText(font42, "0", &wSeconds2, &hSeconds2);
	timeSeconds2R.x = 880;
	timeSeconds2R.y = 10;
	timeSeconds2R.w = wSeconds2;
	timeSeconds2R.h = hSeconds2;

	//Anzeige Time-Point
	SDL_Surface* timePointS = TTF_RenderText_Solid(font42, ":", black);
	timePointTex = SDL_CreateTextureFromSurface(renderer, timePointS);
	SDL_FreeSurface(timePointS);

	int wTimePoint = 0;
	int hTimePoint = 0;
	TTF_SizeText(font42, ":", &wTimePoint, &hTimePoint);
	timePointR.x = 830;
	timePointR.y = 8;
	timePointR.w = wTimePoint;
	timePointR.h = hTimePoint;
	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;


		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				MoveLeft = true;
				break;

			case SDLK_d:
				MoveRight = true;
				break;

			case SDLK_w:
				MoveUp = true;
				break;

			case SDLK_s:
				MoveDown = true;
				break;

			case SDLK_LEFT:
				MoveLeft = true;
				break;

			case SDLK_RIGHT:
				MoveRight = true;
				break;

			case SDLK_UP:
				MoveUp = true;
				break;

			case SDLK_DOWN:
				MoveDown = true;
				break;

			default:
				break;
			}
			break;
		

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				MoveLeft = false;
				break;

			case SDLK_d:
				MoveRight = false;
				break;

			case SDLK_w:
				MoveUp = false;
				break;

			case SDLK_s:
				MoveDown = false;
				break;

			case SDLK_LEFT:
				MoveLeft = false;
				break;

			case SDLK_RIGHT:
				MoveRight = false;
				break;

			case SDLK_UP:
				MoveUp = false;
				break;

			case SDLK_DOWN:
				MoveDown = false;
				break;

			case SDLK_1:
				geschwindigkeitPress = true;
				break;

			default:
				break;
			}
			break;

		default:
			break;
	}
}

void Game::update()
{
	
	cnt++;
	//std::cout << cnt << std::endl;


	if (score == 15) {
		isRunning = false;
	}

	if (geschwindigkeitPress == true && geschwindigkeit < 6) {
		geschwindigkeit++;
		geschwindigkeitPress = false;
	}


	//Timer aktualisieren
	if (cnt % 60 == 0)
	{

		if (sekunden2 == 0)
		{
			sekunden2 = 9;

			if (sekunden1 == 0)
			{
				sekunden1 = 5;
				minuten--;
				if (minuten == 0)
				{
					colorTime = { 255, 255, 0 };
				}

			}
			else
			{
				sekunden1--;
			}
			
		}
		else
		{
			sekunden2--;
			if (minuten == 0 && sekunden1 == 1 && sekunden2 == 5)
			{
				colorTime = { 255, 0, 0 };
			}

			if (minuten == 0 && sekunden1 == 3 && sekunden2 == 0)
			{
				colorTime = { 255, 165, 0 };
			}
		}
		
		//Minuten
		std::string tmp1 = std::to_string(minuten);
		char const* minutes_char = tmp1.c_str();
		SDL_Surface* timeMinutesS = TTF_RenderText_Solid(font42, minutes_char, colorTime);
		timeMinutesTex = SDL_CreateTextureFromSurface(renderer, timeMinutesS);
		SDL_FreeSurface(timeMinutesS);
		int wMinutes = 0;
		int hMinutes = 0;
		TTF_SizeText(font42, minutes_char, &wMinutes, &hMinutes);
		timeMinutesR.w = wMinutes;
		timeMinutesR.h = hMinutes;

		//Anzeige Sekunden1
		std::string tmp2 = std::to_string(sekunden1);
		char const* seconds1_char = tmp2.c_str();
		SDL_Surface* timeSeconds1S = TTF_RenderText_Solid(font42, seconds1_char, colorTime);
		timeSeconds1Tex = SDL_CreateTextureFromSurface(renderer, timeSeconds1S);
		SDL_FreeSurface(timeSeconds1S);
		int wSeconds1 = 0;
		int hSeconds1 = 0;
		TTF_SizeText(font42, seconds1_char, &wSeconds1, &hSeconds1);
		timeSeconds1R.w = wSeconds1;
		timeSeconds1R.h = hSeconds1;

		//Anzeige Sekunden2
		std::string tmp3 = std::to_string(sekunden2);
		char const* seconds2_char = tmp3.c_str();
		SDL_Surface* timeSeconds2S = TTF_RenderText_Solid(font42, seconds2_char, colorTime);
		timeSeconds2Tex = SDL_CreateTextureFromSurface(renderer, timeSeconds2S);
		SDL_FreeSurface(timeSeconds2S);
		int wSeconds2 = 0;
		int hSeconds2 = 0;
		TTF_SizeText(font42, seconds2_char, &wSeconds2, &hSeconds2);
		timeSeconds2R.w = wSeconds2;
		timeSeconds2R.h = hSeconds2;
		
	}


	//Punkt auf Karte erzeugen
	if (cnt % 120 == 0 && arrayFuellmenge < 10 && counterPoints < 15)
	{
		int zahlX;
		int zahlY;

		struct IntPair ret;

		ret = map->ChangeMapAddPoint(level);

		zahlX = ret.second;
		zahlY = ret.first;

		cout << zahlX << zahlY;

		points[arrayFuellmenge][0] = zahlX;
		points[arrayFuellmenge][1] = zahlY;
		arrayFuellmenge++;
		counterPoints++;
	}
	
	
	//Höhe und Breite des Charakters
	destR.h = 75;
	destR.w = 75;
	

	//Spielfeldgröße: 1600*800 

	
	if (MoveRight && x < 1493) {
		x = x + geschwindigkeit;
		if (x > 1493) {
			x = 1493;
		}
		destR.x = x;
	}
	if (MoveLeft && x > 192) {
		x = x - geschwindigkeit;
		if (x < 192) {
			x = 192;
		}
		destR.x = x;
	}
	if (MoveUp && y > 64) {
		y = y - geschwindigkeit;
		if (y < 64) {
			y = 64;
		}
		destR.y = y;
	}
	if (MoveDown && y < 693) {
		y = y + geschwindigkeit;
		if (y > 693) {
			y = 693;
		}
		destR.y = y;
	}

	//Punkt wieder von der Karte entfernen
	if (arrayFuellmenge > 0)
	{
		for (int i = 0; i < arrayFuellmenge; i++)
		{
			int pointX = points[i][0] * 32 + 16;
			int pointY = points[i][1] * 32 + 16;


			if (x >= pointX - 75 && x <= pointX && y >= pointY - 75 && y <= pointY)
			{
				cout << "Punkt erreicht";
				map->ChangeMapRemovePoint(points[i][1], points[i][0], level);

				//Anzeige des Scores erhöhen
				score++;
				std::string tmp = std::to_string(score);
				char const* score_char = tmp.c_str();
				SDL_Surface* scoreS = TTF_RenderText_Solid(font42, score_char, yellow);
				scoreTex = SDL_CreateTextureFromSurface(renderer, scoreS);
				SDL_FreeSurface(scoreS);
				int wScore = 0;
				int hScore = 0;
				TTF_SizeText(font42, score_char, &wScore, &hScore);
				scoreR.w = wScore;
				scoreR.h = hScore;
				
				//array umschreiben
				for (int j = i; j < arrayFuellmenge-1; j++) {
					points[j][0] = points[j + 1][0];
					points[j][1] = points[j + 1][1];
				}

				arrayFuellmenge--;
			}

		}
		
		


	}
 
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	//this is where we would add stuff to render
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	SDL_RenderCopy(renderer, textScoreTex, NULL, &textScoreR);
	SDL_RenderCopy(renderer, scoreTex, NULL, &scoreR);
	SDL_RenderCopy(renderer, timeMinutesTex, NULL, &timeMinutesR);
	SDL_RenderCopy(renderer, timeSeconds1Tex, NULL, &timeSeconds1R);
	SDL_RenderCopy(renderer, timeSeconds2Tex, NULL, &timeSeconds2R);
	SDL_RenderCopy(renderer, timePointTex, NULL, &timePointR);
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}