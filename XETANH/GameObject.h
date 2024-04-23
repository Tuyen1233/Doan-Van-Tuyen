#pragma once
#pragma once
#include"Game.h"
#include"Map.h"
#include "Bullet.h"

#include<vector>
class GameObject {

public:

	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void handles(SDL_Event& event, std::vector<Bullet*>& bullets2, std::vector<Bullet*>& bullets, bool & dead);
	void handles2(SDL_Event& event, std::vector<Bullet*>& bullets, std::vector<Bullet*>& bullets2,bool &dead2);
	bool checkCollision(int bulletX, int bulletY, int tankX, int tankY);
	void Update();
	void Render();
	void Render2();


	void setInitialPosition(int x, int y) { initialX = x; initialY = y; }
	int getX();
	int getY();



private:
	int initialX; // V? trí ban ??u
	int initialY; // V? trí ban ??u
	
	int xpos;
	int ypos;
	int delay{ 1 };
	float angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	float angle2 = 0;
	SDL_RendererFlip flip2 = SDL_FLIP_NONE;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};


