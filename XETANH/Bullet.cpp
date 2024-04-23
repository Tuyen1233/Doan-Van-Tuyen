#include "Bullet.h"
#include"TextureManager.h"
#include"Game.h"

Bullet::Bullet(int x, int y, float angle3) : xpos(x), ypos(y), angle3(angle3), destroyed(false) {
    texture = TextureManager::LoadTexture("0 bit/d3.png");

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32; // Width of bullet texture
    srcRect.h = 32; // Height of bullet texture

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 32; // Width of bullet on screen
    destRect.h = 32; // Height of bullet on screen

}

Bullet::~Bullet() {
    SDL_DestroyTexture(texture);
}

void Bullet::Update() {
    // Update bullet position based on angle and speed
    xpos += static_cast<int>(speed * cos(angle3 * M_PI / 180));
    ypos -= static_cast<int>(speed * sin(angle3 * M_PI / 180));

   


    destRect.x = xpos;
    destRect.y = ypos;
    int lvl2[20][25] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,2,1,1,1,1,0,0,0,0,0,0,0,0,0,2,0,0,0,2},
    {2,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,2},
    {2,0,0,0,0,2,2,1,1,1,1,1,2,0,0,0,0,1,1,1,1,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,1,0,0,2,2,2,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2},
    {2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

    };
    int xx = xpos / 32;
    int yy = ypos / 32;
    // Check if bullet is out of screen or hit a tile, then destroy it
    //if(angle3==90){  if (lvl2[yy + 1][xx] == 2) { destroyed = true; }}
      
    
    //else if (angle3 == 180) { if (lvl2[yy ][xx-1] == 2) { destroyed = true; }}
       
    
     if (angle3 == 0 || angle3 == -90) {
        if (xpos < 0 || xpos > 800 || ypos < 0 || ypos > 640 || lvl2[yy][xx] == 2) {
            destroyed = true;
        }
    }
     else if (angle3 == 90) {
         if (lvl2[yy+1][xx] == 2) { destroyed = true; }
     }
     else if (angle3 == 180) {
         if (lvl2[yy ][xx+1] == 2) { destroyed = true; }
     }

}
int Bullet::getX()  { return xpos; }
int Bullet::getY()  { return ypos; }

void Bullet::Render() {
    // Render bullet texture at its position
    SDL_RenderCopyEx(Game::renderer, texture, NULL, &destRect, angle3, NULL, SDL_FLIP_NONE);
}

bool Bullet::IsDestroyed() {
    return destroyed;
}