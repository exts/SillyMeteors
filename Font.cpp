#include "font.hpp"

Font::Font(std::string path, int font_size)
{
    //load font
    load(path, font_size);
}

void Font::load(std::string path, int font_size)
{
    //lets try loading the font
    font = font_ptr(TTF_OpenFont(path.c_str(), font_size));
    if(!font) {
        font_loaded = false;
    }
}

void Font::draw(std::string text, SDL_Renderer *renderer, 
    SDL_Color color, int x, int y, int align_x, int align_y)
{
    //can't draw what doesn't exist
    if(!font_loaded) return;

    //temp font surface
    surf_ptr font_surf(TTF_RenderText_Blended(font.get(), text.c_str(), color));

    if(font_surf == nullptr) {
        std::cout << "Couldn't create font surface for: " << text << std::endl;
        return;
    }

    //temp font texture
    text_ptr font_text(SDL_CreateTextureFromSurface(renderer, font_surf.get()));

    if(font_text == nullptr) {
        std::cout << "Couldn't create font texture for: " << text << std::endl;
        return;
    }   

    //get size text
    int score_font_w = 0, score_font_h = 0;
    if(TTF_SizeText(font.get(), text.c_str(), &score_font_w, &score_font_h) == -1) {
        std::cout << "Couldn't get font size for: " << text << std::endl;
        return;
    }

    //position of font
    SDL_Rect font_pos;
    font_pos.w = score_font_w;
    font_pos.h = score_font_h;
    font_pos.x = x;
    font_pos.y = y;

    //x align offset: 0 = left, 1 = center, 2 = right
    switch(align_x) {
        case 1:
            font_pos.x = ((Game::getWidth() / 2) - (font_pos.w / 2)) + x;
            break;
        case 2:
            font_pos.x = (Game::getWidth() - font_pos.w) + x;
            break;
    }

    //y align offset: 0 = left, 1 = center, 2 = right
    switch(align_y) {
        case 1:
            font_pos.y = (Game::getHeight() / 2 - font_pos.h / 2) + y;
            break;
        case 2:
            font_pos.y = (Game::getHeight() - font_pos.h) + y;
            break;
    }

    //draw font
    SDL_RenderCopy(renderer, font_text.get(), NULL, &font_pos);
}
