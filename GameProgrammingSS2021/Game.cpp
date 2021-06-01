#include "Game.h"

SDL_Texture* playerTex;
SDL_Rect scrR, destR;

Game::Game()
{}
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
			SDL_SetRenderDrawColor(renderer, 255, 127, 0, 0);
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

		default:
			break;
	}
}

void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;
	
	destR.h = 75;
	destR.w = 75;
	
	//800*600
	if (!runterBewegen) {
		if (richtung) {
			destR.x = x++;
		}
		else {
			destR.x = x--;
		}
	}
	
	if (x == 725)
	{
		richtung = false;
		runterBewegen = true;
		y++;
	}

	if (x == 0)
	{
		richtung = true;
		runterBewegen = true;
		y++;
	}

	if (runterBewegen) {
		if (y % 75 != 0) {
			destR.y = y++;
		}
		else {
			runterBewegen = false;
		}
	}

	if (y == 525)
	{
		y = 0;
	}
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}