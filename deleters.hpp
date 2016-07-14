#ifndef DELETER_H
#define DELETER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

//delete for unique_ptr textures
//http://codereview.stackexchange.com/questions/71734/simon-says-four-tiles-game-with-c-and-sdl
//Actual Post: http://codereview.stackexchange.com/a/71859
struct texture_delete
{
    void operator()(SDL_Texture * texture) const
    {
        if(texture != nullptr) {
            SDL_DestroyTexture(texture);
            // std::cout << "Deleting texture" << std::endl;
        }
    }
};

struct font_delete
{
    void operator()(TTF_Font *font) const
    {
        if(font != nullptr) {
            TTF_CloseFont(font);
            // std::cout << "Clearing font memory" << std::endl;
        }
    }
};

struct surface_delete
{
    void operator()(SDL_Surface *surface) const
    {
        if(surface != nullptr) {
            SDL_FreeSurface(surface);
        }
    }
};

#endif