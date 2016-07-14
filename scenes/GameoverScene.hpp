#ifndef GAMEOVER_SCENE_H
#define GAMEOVER_SCENE_H

//std
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

//sdl
//game
#include "../game.hpp"
#include "../font.hpp"

#include "scene.hpp"
#include "levelscene.hpp"

class GameoverScene : public Scene
{

    typedef std::unique_ptr<Font> font_ptr;
    font_ptr go_text;
    font_ptr lvl_text;

public:

    GameoverScene(){}
    virtual ~GameoverScene();

    void load(SDL_Renderer *renderer);
    void events(SDL_Event e);
    void update(float delta);
    void draw(SDL_Renderer *renderer);

};

#endif