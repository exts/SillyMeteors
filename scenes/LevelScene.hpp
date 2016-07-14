#ifndef SCENES_LEVEL_SCENE_H
#define SCENES_LEVEL_SCENE_H

//game
#include "scene.hpp"
// #include "../sprite.hpp"
// #include "../spritesmap.hpp"
#include "../game.hpp"
#include "../sprite.hpp"
#include "../font.hpp"
#include "../deleters.hpp"
#include "../scenemanager.hpp"

//std
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

//sdl
#include "SDL_ttf.h"

class LevelScene : public Scene 
{
    static int level;

    //font
    std::unique_ptr<Font> level_font;
    std::unique_ptr<Font> level_text_font;
    std::unique_ptr<Sprite> background;

public:

    LevelScene(){}
    virtual ~LevelScene();

    void load(SDL_Renderer *renderer);
    void events(SDL_Event e);
    void update(float delta);
    void draw(SDL_Renderer *renderer);

    static int getLevel();
    static void setLevel(int level);

    void drawLevel(SDL_Renderer *renderer);
};

#endif