#pragma once
#include "Game.h"

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:

	SDL_Rect src, dest;
	SDL_Renderer* renderer;

	SDL_Texture* limitation;
	SDL_Texture* background;

	int map[20][25];
};