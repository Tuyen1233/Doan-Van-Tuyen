#pragma once
#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Map.h"
#include<vector>

enum GameState {
	MENU,
	PLAY,
	PLAY2,
	EXIT,
	EXIT2,
	EXIT3,
};

class Game
{
public:

	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents(int & kk);
	void update(int & kk);
	bool running() { return isRunning; }
	void render();
	void clean();

	bool dead;
	bool dead2;
	bool dead3;
	


	static SDL_Renderer* renderer;

private:
	
	bool isRunning = false;
	bool hasEnded{ false };
	int cnt = 155;
	SDL_Window* window;
	// Khai báo vector ch?a ??n
	std::vector<Bullet*> bullets;


	// Khai báo t?c ?? c?a ??n
	int k = 0;



	GameState gameState;

	void renderMenu();
	void handleEventsMenu(int & kk);
	void renderInstructions(SDL_Texture* instructionsTexture);
	void renderResult(SDL_Texture* instructionsTexture);
	void renderResult2(SDL_Texture* instructionsTexture);
	void renderResult3(SDL_Texture* instructionsTexture);

};
