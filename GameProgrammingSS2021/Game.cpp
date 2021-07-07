#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <random>

SDL_Texture* playerTex;
SDL_Texture* textScoreTex;
SDL_Texture* scoreTex;
SDL_Texture* timeMinutesTex;
SDL_Texture* timeSeconds1Tex;
SDL_Texture* timeSeconds2Tex;
SDL_Texture* timePointTex;
SDL_Texture* textLevelTex;
SDL_Texture* levelNumberTex; 
SDL_Texture* textBonusTex;
SDL_Texture* bonusNumberTex;
SDL_Rect scrR, destR;
SDL_Rect textScoreR;
SDL_Rect scoreR;
SDL_Rect textLevelR, levelNumberR;
SDL_Rect timeMinutesR, timeSeconds1R, timeSeconds2R, timePointR;
SDL_Rect textBonusR, bonuslNumberR; 
TTF_Font* font42;
TTF_Font* font28;
SDL_Color yellow = { 255, 255, 0 };
SDL_Color black = { 0, 0, 0 };
SDL_Color green = { 0, 255, 0 };
SDL_Color colorTime = { 0, 255, 0 };


struct IntPair {
	int first, second;
};

struct ReturnGame {
	int score;
	bool run;
	int bonus;
};

struct WallReturn {
	int x;
	int y;
};

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(int gamelevel, int gameScore, int bonus)
{
	level = gamelevel;
	score = gameScore;
	countBonusPoints = bonus;

	switch (level)
	{

	case 1:
		levelMaxPoints = 15;
		break;
	case 2:
		levelMaxPoints = 20;
		break;
	case 3:
		levelMaxPoints = 30;
		break;
	case 4:
		levelMaxPoints = 40;
		break;
	case 5:
		levelMaxPoints = 50;
		break;
	case 6:
		levelMaxPoints = 60;
		break;
	case 7:
		levelMaxPoints = 70;
		break;
	case 8:
		levelMaxPoints = 80;
		break;
	case 9:
		levelMaxPoints = 90;
		break;
	case 10:
		levelMaxPoints = 100;
		break;

	default:
		break;
	}

	
	//Zufallszahl erzeugen (in welchem zeitlichen Abstand erscheinen die Bonuspunkte)
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(900, 2700);
	zufallszahlBonus = distr(eng);
	std::cout << "Zufallszahl: " << zufallszahlBonus << std::endl;
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


	//Anzahl der Hindernisse im Level ermitteln
	counterWall = map->CountWall(level);
	std::cerr << "AnzahlWall: " << counterWall << std::endl;

	//Hindernisse feststellen und ins Array schreiben
	for (int i = 0; i < counterWall; i++)
	{
		int x = 0;
		int y = 0;
		struct WallReturn returnWall;
		returnWall = map->ReturnWallPosition(i, level);
		x = returnWall.x;
		y = returnWall.y;

		std::cout << "WallX Nr. " << i << ": " << x << std::endl;
		std::cout << "WallY Nr. " << i << ": " << y << std::endl;

		wallArray[i][0] = x;
		wallArray[i][1] = y;
	}


	if (TTF_Init() == -1)
	{
		std::cerr << "Konnte SDL_ttf nicht initialisieren! Fehler: " << TTF_GetError() << std::endl;
	}

	font42 = TTF_OpenFont("assets/arial.ttf", 42);
	if (!font42)
	{
		std::cerr << "Konnte Schriftart nicht laden! Fehler: " << TTF_GetError() << std::endl;
	}
	font28 = TTF_OpenFont("assets/arial.ttf", 28);
	if (!font28)
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
	std::string tmpScore = std::to_string(score);
	char const* score_char = tmpScore.c_str();
	SDL_Surface* scoreS = TTF_RenderText_Solid(font42, score_char, yellow);
	scoreTex = SDL_CreateTextureFromSurface(renderer, scoreS);
	SDL_FreeSurface(scoreS);

	int wScore = 0;
	int hScore = 0;
	TTF_SizeText(font42, score_char, &wScore, &hScore);
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

	//Anzeige Text Level
	SDL_Surface* textLevelS = TTF_RenderText_Solid(font42, "Level:", yellow);
	textLevelTex = SDL_CreateTextureFromSurface(renderer, textLevelS);
	SDL_FreeSurface(textLevelS);

	int wTextLevel = 0;
	int hTextLevel = 0;
	TTF_SizeText(font42, "Level:", &wTextLevel, &hTextLevel);
	textLevelR.x = 200;
	textLevelR.y = 10;
	textLevelR.w = wTextLevel;
	textLevelR.h = hTextLevel;

	//Anzeige LevelNumber
	std::string tmpLevelNumber = std::to_string(level);
	char const* level_char = tmpLevelNumber.c_str();
	SDL_Surface* levelNumberS = TTF_RenderText_Solid(font42, level_char, yellow);
	levelNumberTex = SDL_CreateTextureFromSurface(renderer, levelNumberS);
	SDL_FreeSurface(levelNumberS);

	int wLevelNumber = 0;
	int hLevelNumber = 0;
	TTF_SizeText(font42, level_char, &wLevelNumber, &hLevelNumber);
	levelNumberR.x = 320;
	levelNumberR.y = 10;
	levelNumberR.w = wLevelNumber;
	levelNumberR.h = hLevelNumber;

	//Anzeige Text Bonuspunkte
	SDL_Surface* textBonusS = TTF_RenderText_Solid(font28, "Bonuspunkte:", green);
	textBonusTex = SDL_CreateTextureFromSurface(renderer, textBonusS);
	SDL_FreeSurface(textBonusS);

	int wTextBonus = 0;
	int hTextBonus = 0;
	TTF_SizeText(font28, "Bonuspunkte:", &wTextBonus, &hTextBonus);
	textBonusR.x = 10;
	textBonusR.y = 70;
	textBonusR.w = wTextBonus;
	textBonusR.h = hTextBonus;

	//Anzeige Bonuspunkte
	std::string tmpBonusNumber = std::to_string(countBonusPoints);
	char const* bonus_char = tmpBonusNumber.c_str();
	SDL_Surface* bonusNumberS = TTF_RenderText_Solid(font42, bonus_char, green);
	bonusNumberTex = SDL_CreateTextureFromSurface(renderer, bonusNumberS);
	SDL_FreeSurface(bonusNumberS);

	int wBonusNumber = 0;
	int hBonusNumber = 0;
	TTF_SizeText(font42, bonus_char, &wBonusNumber, &hBonusNumber);
	bonuslNumberR.x = ((6*32) - wBonusNumber) /2;
	bonuslNumberR.y = 100;
	bonuslNumberR.w = wBonusNumber;
	bonuslNumberR.h = hBonusNumber;
	
}

void Game::handleEvents()
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


	if (scoreLevel == levelMaxPoints) {
		isRunning = false;
	}

	if (geschwindigkeitPress == true && geschwindigkeit < 6) {
		geschwindigkeit++;
		geschwindigkeitPress = false;
	}


	//Timer aktualisieren, alle 60 Frames
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
		
		//Anzeige Minuten
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
	if (cnt % 60 == 0 && arrayFuellmenge < 10 && counterPoints < levelMaxPoints)
	{
		int zahlX;
		int zahlY;

		struct IntPair ret;

		//verhindern, dass Punkte an bereits besetzten Stellen erscheinen
		do {
			ret = map->ChangeMapAddPoint(level, true);

			zahlX = ret.second;
			zahlY = ret.first;
		}
		while (zahlX == 0 && zahlY == 0);

		cout << zahlX << zahlY;

		points[arrayFuellmenge][0] = zahlX;
		points[arrayFuellmenge][1] = zahlY;
		arrayFuellmenge++;
		counterPoints++;
	}

	//Bonuspunkte auf Karte anzeigen
	if (cnt % zufallszahlBonus == 0 && bonusOnMap == false) {
		
		struct IntPair ret;

		do {
			ret = map->ChangeMapAddPoint(level, false);

			bonusPointX = ret.second;
			bonusPointY = ret.first;
		} while (bonusPointX == 0 && bonusPointY == 0);

		bonusOnMap = true;
	}


	//H�he und Breite des Charakters
	destR.h = 75;
	destR.w = 75;


	//Spielfeldgr��e: 1600*800 

	//Charakter kann die Spielfeldbegrenzung nicht verlassen
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

	int xWall = 0;
	int yWall = 0;
	for (int i = 0; i < counterWall; i++)
	{
		xWall = wallArray[i][0];
		yWall = wallArray[i][1];

		//std::cout << i << "xWall: " << xWall << ", yWall:  " << yWall << std::endl;

		//Ber�hrung von links
		if (MoveRight && x > ((xWall * 32) - 75) && x < ((xWall * 32) + 10 - 75) && y > ((yWall * 32) - 75) && y < ((yWall * 32) + 32))
		{
			x = (xWall * 32) - 75;
			destR.x = x;
		}

		//Ber�hrung von rechts
		if (MoveLeft && x < ((xWall * 32) + 32) && x > ((xWall * 32) + 32 - 10) && y > ((yWall * 32) - 75) && y < ((yWall * 32) + 32))
		{
			x = (xWall * 32) + 32;
			destR.x = x;
		}

		//Ber�hrung von oben
		if (MoveDown && y > ((yWall * 32) - 75) && y < ((yWall * 32) + 10 - 75) && x > ((xWall * 32) - 75) && x < ((xWall * 32) + 32))
		{
			y = (yWall * 32) - 75;
			destR.y = y;
		}

		//Ber�hrung von unten
		if (MoveUp && y < ((yWall * 32) + 32) && y > ((yWall * 32) + 32 - 10) && x > ((xWall * 32) - 75) && x < ((xWall * 32) + 32))
		{
			y = (yWall * 32) + 32;
			destR.y = y;
		}

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

				//Anzeige des Scores erh�hen
				score++;
				scoreLevel++;
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

	if (bonusOnMap)
	{
		int pointX = bonusPointX * 32 + 16;
		int pointY = bonusPointY * 32 + 16;

		if (x >= pointX - 75 && x <= pointX && y >= pointY - 75 && y <= pointY)
		{
			cout << "Bonus erreicht";
			map->ChangeMapRemovePoint(bonusPointY, bonusPointX, level);

			bonusOnMap = false;
			countBonusPoints++;


			//Anzeige Bonuspunkte
			std::string tmpBonusNumber = std::to_string(countBonusPoints);
			char const* bonus_char = tmpBonusNumber.c_str();
			SDL_Surface* bonusNumberS = TTF_RenderText_Solid(font42, bonus_char, green);
			bonusNumberTex = SDL_CreateTextureFromSurface(renderer, bonusNumberS);
			SDL_FreeSurface(bonusNumberS);

			int wBonusNumber = 0;
			int hBonusNumber = 0;
			TTF_SizeText(font42, bonus_char, &wBonusNumber, &hBonusNumber);
			bonuslNumberR.x = ((6 * 32) - wBonusNumber) / 2;
			bonuslNumberR.y = 100;
			bonuslNumberR.w = wBonusNumber;
			bonuslNumberR.h = hBonusNumber;


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
	SDL_RenderCopy(renderer, textLevelTex, NULL, &textLevelR);
	SDL_RenderCopy(renderer, levelNumberTex, NULL, &levelNumberR);
	SDL_RenderCopy(renderer, textBonusTex, NULL, &textBonusR);
	SDL_RenderCopy(renderer, bonusNumberTex, NULL, &bonuslNumberR);
	
	SDL_RenderPresent(renderer);
}

struct ReturnGame Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

	struct ReturnGame ret;
	ret.score = score;
	ret.run = stopAll;
	ret.bonus = countBonusPoints;

	return ret;
}