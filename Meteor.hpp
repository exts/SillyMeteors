#ifndef METEOR_H
#define METEOR_H

//sdl
#include "SDL.h"
#include "SDL_image.h"

//std
#include <cmath>
#include <string>
#include <vector>

//game
#include "game.hpp"
#include "sprite.hpp"
#include "spritesmap.hpp"

class Meteor
{
    bool loaded = false;

    float f_x = 0.0f;
    float f_y = 0.0f;
    float f_width = 0.0f;
    float f_height = 0.0f;

    Sprite *sprite = nullptr;

    SDL_Rect src;
    SDL_Rect dst;

    //all about speed (mainly for growing the meteor)
    float delta = 0.0f;
    float speed = 3.0f;
    float steps = 1.0f; //speed * steps = actual distance we move

    //movement
    float speed_x = 5.0f;
    float speed_y = 5.0f;
    float speed_s = 4.0f; //speed steps

public:

    Meteor(){}
    Meteor(std::string name, Spritesmap *s_map);

    /* add dimensions */
    SDL_Rect getDims();
    void addDims(float w, float h);

    /* set position */
    void setPosition(int x, int y);

    /* draw meteor */
    void draw(SDL_Renderer * renderer);

    /* set delta/speed/steps */
    void setSteps(float f_steps);
    void setSpeedX(float f_speed);
    void setSpeedY(float f_speed);
    void setSpeed(float f_speed);
    void setDelta(float f_delta);
    void setDirection(int x, int y);

    /* get velocity */
    float getVelocity();
    float getxVelocity();
    float getyVelocity();

    /* grow meteor */
    void grow(float delta);

    /* grow meteor */
    void move(float delta);
};

#endif