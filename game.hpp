#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"

#include "base.hpp"
#include "scenemanager.hpp"

class Game : public Base
{
    SceneManager m_scenes;
public:
    Game(){}
    void draw();
    void loadAssets();
    void events(SDL_Event e);
    void update(float delta);
};

#endif