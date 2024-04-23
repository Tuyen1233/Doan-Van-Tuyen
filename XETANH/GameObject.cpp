#include "GameObject.h"
#include "TextureManager.h"
#include<iostream>
#include"Map.h"
#include <cmath>
#include"Bullet.h"
#include"Game.h"
GameObject::GameObject(const char* texturesheet, int x, int y) {

    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
    initialX = x; // L?u v? trí ban ??u
    initialY = y; // L?u v? trí ban ??u
}




bool GameObject::checkCollision(int bulletX, int bulletY, int tankX, int tankY) {
    // Tính toán các tọa độ của hình chữ nhật bao quanh đạn và xe tăng
    int bulletLeft = bulletX;
    int bulletRight = bulletX + 32; // Giả sử BULLET_WIDTH là chiều rộng của đạn
    int bulletTop = bulletY;
    int bulletBottom = bulletY + 32; // Giả sử BULLET_HEIGHT là chiều cao của đạn

    int tankLeft = tankX;
    int tankRight = tankX + 32; // tankWidth là chiều rộng của xe tăng
    int tankTop = tankY;
    int tankBottom = tankY + 32;// tankHeight là chiều cao của xe tăng

    // Kiểm tra xem hai hình chữ nhật có chồng lấp nhau không 
    if (bulletRight > tankLeft && bulletLeft < tankRight && bulletBottom >tankTop && bulletTop < tankBottom) {
        // Nếu có chồng lấp, tức là có va chạm
        return true;
    }

    // Nếu không có chồng lấp, không có va chạm
    return false;
}

void GameObject::handles(SDL_Event& event, std::vector<Bullet*>& bullets2, std::vector<Bullet*>& bullets, bool & dead) {
    int x = xpos / 32;
    int y = ypos / 32;
    int sodo[20][25] = {
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


    switch (event.key.keysym.sym) {
    case SDLK_UP:
        if (angle2 != 90)
        {
            angle2 = 90;
            flip2 = SDL_FLIP_VERTICAL;
            break;
        }
        // X? lý di chuy?n lên

        if (sodo[y - 1][x] == 2) {}
        else if (sodo[y - 1][x] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); ypos -= 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);

            ypos -= 32;
        }
        break;
    case SDLK_DOWN:
        if (angle2 != -90)
        {
            angle2 = -90;
            flip2 = SDL_FLIP_VERTICAL;
            break;
        }
        // X? lý di chuy?n xu?ng
        if (sodo[y + 1][x] == 2) {}
        else if (sodo[y + 1][x] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); ypos += 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            ypos += 32;
        }

        break;
    case SDLK_LEFT:
        // X? lý di chuy?n sang trái
        if (angle2 != 180)
        {
            angle2 = 180;
            //flip = SDL_FLIP_NONE;
            break;
        }
        if (sodo[y][x - 1] == 2) {}
        else if (sodo[y][x - 1] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); xpos -= 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            xpos -= 32;
        }
        break;
    case SDLK_RIGHT:
        // X? lý di chuy?n sang ph?i
        if (angle2 != 0)
        {
            angle2 = 0;
            break;
        }
        if (sodo[y][x + 1] == 2) {}
        else if (sodo[y][x + 1] == 1) { SDL_SetTextureAlphaMod(objTexture, 30); xpos += 32; }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            xpos += 32;
        }
        break;
    case SDLK_m:
    {
        int offsetX, offsetY;
        switch ((int)angle2)
        {
        case 0:
            offsetX = 1; offsetY = 0; break;
        case 180:
            offsetX = -1; offsetY = 0; break;
        case 90:
            offsetX = 0; offsetY = -1; break;
        case -90:
            offsetX = 0; offsetY = 1; break;
        }
        Bullet* bullet = new Bullet(xpos + offsetX * 32, ypos + offsetY * 32, angle2);
        bullets.push_back(bullet);

        break;
    }

    default:
        break;
    }

    for (auto& bullet : bullets2) {
         
       
         if (checkCollision(bullet->getX(), bullet->getY(), xpos, ypos)) {
            // N?u có va ch?m, ??t l?i v? trí c?a c? hai nhân v?t v? v? trí ban ??u
            
            xpos = initialX; // ??t l?i v? trí c?a nhân v?t
            ypos = initialY;

            std::cout << "Lose"; bullet->destroy();
            dead = true;
            

          
           
        }
    }


}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
}






void GameObject::handles2(SDL_Event& event, std::vector<Bullet*>& bullets, std::vector<Bullet*>& bullets2,bool &dead2) {
    int x = xpos / 32;
    int y = ypos / 32;
    int sodo[20][25] = {
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
    switch (event.key.keysym.sym) {
    case SDLK_w:
        if (angle != 90)
        {
            angle = 90;
            flip = SDL_FLIP_VERTICAL;
            break;
        }
        // X? lý di chuy?n lên

        if (sodo[y - 1][x] == 2) {}
        else if (sodo[y - 1][x] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); ypos -= 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);

            ypos -= 32;
        }
        break;
    case SDLK_s:
        if (angle != -90)
        {
            angle = -90;
            flip = SDL_FLIP_VERTICAL;
            break;
        }
        // X? lý di chuy?n xu?ng
        if (sodo[y + 1][x] == 2) {}
        else if (sodo[y + 1][x] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); ypos += 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            ypos += 32;
        }

        break;
    case SDLK_a:
        // X? lý di chuy?n sang trái
        if (angle != 180)
        {
            angle = 180;
            //flip = SDL_FLIP_NONE;
            break;
        }
        if (sodo[y][x - 1] == 2) {}
        else if (sodo[y][x - 1] == 1) {
            SDL_SetTextureAlphaMod(objTexture, 30); xpos -= 32;
        }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            xpos -= 32;
        }
        break;
    case SDLK_d:
        // X? lý di chuy?n sang ph?i
        if (angle != 0)
        {
            angle = 0;
            break;
        }
        if (sodo[y][x + 1] == 2) {}
        else if (sodo[y][x + 1] == 1) { SDL_SetTextureAlphaMod(objTexture, 30); xpos += 32; }
        else {
            SDL_SetTextureAlphaMod(objTexture, 255);
            xpos += 32;
        }
        break;
    case SDLK_f:
    {
        int offsetX, offsetY;
        switch ((int)angle)
        {
        case 0:
            offsetX = 1; offsetY = 0; break;
        case 180:
            offsetX = -1; offsetY = 0; break;
        case 90:
            offsetX = 0; offsetY = -1; break;
        case -90:
            offsetX = 0; offsetY = 1; break;
        }
        Bullet* bullet = new Bullet(xpos + offsetX * 32, ypos + offsetY * 32, angle);
        bullets2.push_back(bullet);
        break;
    }

    default:
        break;
    }
    
    for (auto& bullet : bullets) {
       
        if (checkCollision(bullet->getX(), bullet->getY(), xpos, ypos)) {
            // N?u có va ch?m, ??t l?i v? trí c?a c? hai nhân v?t v? v? trí ban ??u
            std::cout << xpos << ' ' << ypos << std::endl;
           
            xpos = initialX; // ??t l?i v? trí c?a nhân v?t
            ypos = initialY;
           
            std::cout << "Lose";
            bullet->destroy();
            
            dead2 = true;
            // Lo?i b? ??n kh?i trò ch?i
        }
    }
   

}

void GameObject::Update()
{


    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = 32;
    destRect.w = 32;
    destRect.x = xpos;
    destRect.y = ypos;


}

void GameObject::Render()
{
    //SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, -angle, NULL, SDL_FLIP_NONE);

}
void GameObject::Render2()
{
    //SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, -angle2, NULL, SDL_FLIP_NONE);

}





