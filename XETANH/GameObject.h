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

	void handles(SDL_Event& event, std::vector<Bullet*>& bullets, bool & dead);
	void handles2(SDL_Event& event, std::vector<Bullet*>& bullets,bool &dead2);
	void handles3(SDL_Event& event, std::vector<Bullet*>& bullets, bool& dead3);
	bool checkCollision(int bulletX, int bulletY, int tankX, int tankY);
	void Update();
	void Render();
	void Render2();
	void Render3();


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
	float angle2 = 0; float angle3 = 0;
	SDL_RendererFlip flip2 = SDL_FLIP_NONE;
	SDL_RendererFlip flip3= SDL_FLIP_NONE;


	
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};


