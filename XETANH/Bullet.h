#pragma once
#pragma once
#include<SDL.h>
#include<iostream>
class Bullet {
public:
    Bullet(int x, int y, float angle);
    ~Bullet();

    void Update();
    void Render();

    int getX();
    int getY();

    bool IsDestroyed();
    void destroy()
    {
        destroyed = true;
    }
    void print()
    {
        std::cout << xpos << ' ' << ypos << std::endl;
    }
private:
    int xpos;
    int ypos;
    float angle3;
    float speed = 1;
    SDL_Texture* texture;
    bool destroyed;
    SDL_Rect srcRect, destRect;
};
