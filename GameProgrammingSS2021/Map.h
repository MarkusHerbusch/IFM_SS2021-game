#pragma once
#include "Game.h"

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[25][50]);
	void DrawMap();

private:

	SDL_Rect src, dest;
	SDL_Renderer* renderer;

	SDL_Texture* limitation;
	SDL_Texture* background;
	SDL_Texture* backgroundLimitRight;
	SDL_Texture* backgroundLimitBelow;

	int map[25][50];
};