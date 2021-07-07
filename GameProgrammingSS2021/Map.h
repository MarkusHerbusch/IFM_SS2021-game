#pragma once
#include "Game.h"

class Map
{
public:

	Map(int level);
	~Map();



	void LoadMap(int arr[25][50]);
	void DrawMap();
	struct IntPair ChangeMapAddPoint(int level, bool red);
	void ChangeMapRemovePoint(int, int, int);
	int CountWall(int level);
	struct WallReturn ReturnWallPosition(int counterWall, int level);

private:
	
	SDL_Rect src, dest;
	SDL_Renderer* renderer;

	SDL_Texture* limitation;
	SDL_Texture* background;
	SDL_Texture* backgroundLimitRight;
	SDL_Texture* backgroundLimitBelow;
	SDL_Texture* backgroundBlue;
	SDL_Texture* backgroundBlueLimitBelow;
	SDL_Texture* wall;
	SDL_Texture* redPoint;
	SDL_Texture* bonusPoint;

	int map[25][50];
};