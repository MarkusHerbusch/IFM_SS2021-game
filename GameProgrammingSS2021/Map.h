#pragma once
#include "Game.h"

class Map
{
public:

	Map(int level);
	~Map();



	void LoadMap(int arr[25][50]);
	void DrawMap();
	struct IntPair ChangeMapAddPoint(int level);
	void ChangeMapRemovePoint(int, int, int);

private:
	
	SDL_Rect src, dest;
	SDL_Renderer* renderer;

	SDL_Texture* limitation;
	SDL_Texture* background;
	SDL_Texture* backgroundLimitRight;
	SDL_Texture* backgroundLimitBelow;
	SDL_Texture* backgroundBlue;
	SDL_Texture* backgroundBlueLimitBelow;
	SDL_Texture* redPoint;

	int map[25][50];
};