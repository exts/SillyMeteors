//sdl2
#include "SDL.h"
#include "SDL_image.h"

//std
#include <string>
#include <memory>
#include <iostream>

//class declaration
#include "Sprite.hpp"

Sprite::Sprite(SDL_Renderer *renderer, std::string filename, int t_width, int t_height)
{

    f_width = (float) t_width * Game::getWidthRatio();
    f_height = (float) t_height * Game::getHeightRatio();

    // std::cout << Game::getWidthRatio() << ", " << Game::getHeightRatio() << std::endl;
    // std::cout << f_width << ", " << f_height << std::endl << std::endl;

    //set dimensions
    pos.x = 0;
    pos.y = 0;
    pos.w = (int) f_width;
    pos.h = (int) f_height;

    //load texture 
    texture = std::unique_ptr<SDL_Texture, texture_delete>(
        IMG_LoadTexture(renderer, filename.c_str())
    );

    if(texture != nullptr) {
        loaded = true;
    }

}

void Sprite::cleanup()
{
    // std::cout << "Cleaned up..." << std::endl;
    // SDL_DestroyTexture(texture);
}

void Sprite::position(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

bool Sprite::isLoaded()
{
    return loaded;
}

SDL_Texture *Sprite::getTexture()
{
    return texture.get();
}