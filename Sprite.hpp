#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <memory>

#include "game.hpp"
#include "deleters.hpp"

class Sprite 
{

    bool loaded = false;

public:

	// SDL_Texture *texture;
    std::unique_ptr<SDL_Texture, texture_delete> texture = nullptr;
    
    SDL_Rect pos;
    int width = 0, height = 0;

    float f_width = 0.0f, f_height = 0.0f;

    Sprite(){}
    Sprite(SDL_Renderer *renderer, std::string filename, int t_width, int t_height);
    

    bool isLoaded();
    void cleanup();
    void position(int x, int y);

    SDL_Texture *getTexture();
};

#endif