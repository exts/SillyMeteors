#ifndef FONT_H
#define FONT_H

//sdl
#include "SDL.h"
#include "SDL_ttf.h"

//game
#include "game.hpp"
#include "deleters.hpp"

//std
#include <string>
#include <memory>


class Font
{
    typedef std::unique_ptr<TTF_Font, font_delete> font_ptr;
    typedef std::unique_ptr<SDL_Surface, surface_delete> surf_ptr;
    typedef std::unique_ptr<SDL_Texture, texture_delete> text_ptr;
    
    font_ptr font = nullptr;
    bool font_loaded = true;

public:

    Font(std::string path, int font_size);

    void load(std::string path, int font_size);
    void draw(std::string text, SDL_Renderer *renderer, 
        SDL_Color color, int x, int y, int align_x, int align_y);
};

#endif