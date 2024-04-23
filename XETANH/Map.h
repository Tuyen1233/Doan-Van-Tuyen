#pragma once

#include "Game.h"

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	int layvitri(int x, int y);


private:

	SDL_Rect src, dest;
	SDL_Texture* dat;
	SDL_Texture* co;
	SDL_Texture* nuoc;

	int map[20][25];

};

