#ifndef SCENES_GAME_SCENE_H
#define SCENES_GAME_SCENE_H

//game
#include "scene.hpp"
#include "LevelScene.hpp"
#include "../game.hpp"
#include "../font.hpp"
#include "../meteor.hpp"
#include "../sprite.hpp"
#include "../deleters.hpp"
#include "../spritesmap.hpp"
#include "../scenemanager.hpp"

//std
#include <map>
#include <string>
#include <random>
#include <sstream>
#include <iostream>

//sdl
#include "SDL_ttf.h"

class GameScene : public Scene
{
    //window size
    int window_width = 960;
    int window_height = 640;
    int window_height_top_padding = 20; //scoreboard

    //amount of meteors we want to start with when the game starts
    int meteor_start_count = 3;

    //map of sprites
    Spritesmap sprites;

    //vector of meteors
    std::vector<Meteor> meteors;

    //vector of sprite names ex.: mb1, mb2, etc..
    std::vector<std::string> sprite_names;

    //mouse position
    int mouse_x = -1;
    int mouse_y = -1;

    //on click
    bool mouse_down = false;

    //game points
    int points = 0;

    //font stuff
    std::unique_ptr<Font> score_font;

    int countdown = 10;

    //keep count of time between every frme
    float current_time = 0.0f;

    int current_level = 0;

public:
    GameScene(){}
    virtual ~GameScene();

    void load(SDL_Renderer *renderer);
    void events(SDL_Event e);
    void update(float delta);
    void draw(SDL_Renderer *renderer);

    void addMeteors(int count);
    bool secondsPassed(int seconds, float delta);

    void nextLevel();
    void checkLevel();
    void drawScore(SDL_Renderer *renderer);
};

#endif