//game
#include "meteor.hpp"
#include <iostream>

Meteor::Meteor(std::string name, Spritesmap *s_map)
{
    if(!s_map->sprites.empty() && s_map->sprites.count(name) != 0) {

        //for later use (drawing mostly)
        sprite = s_map->get(name);

        //store dimension rect
        src = sprite->pos;
        dst = sprite->pos;

        //set float w/h
        f_width = (float) src.w;
        f_height = (float) src.h;

        //sprite exists
        loaded = true;
    }
}

/* get dimensions */
SDL_Rect Meteor::getDims() 
{
    return dst;
}

/* add dimensions */
void Meteor::addDims(float w, float h)
{
    f_width += w;
    f_height += h;

    dst.w = (int) f_width;
    dst.h = (int) f_height;
}

/* set position */
void Meteor::setPosition(int x, int y)
{

    f_x = (float) x;
    f_y = (float) y;

    dst.x = x;
    dst.y = y;
}

/* draw meteor */
void Meteor::draw(SDL_Renderer * renderer)
{
    SDL_RenderCopy(renderer, sprite->texture.get(), NULL, &dst);
}

/* set delta/speed/steps */
void Meteor::setSteps(float f_steps)
{
    steps = f_steps;
}

void Meteor::setSpeed(float f_speed)
{
    speed = f_speed;
}

void Meteor::setSpeedX(float f_speed)
{
    speed_x = f_speed;
}

void Meteor::setSpeedY(float f_speed)
{
    speed_y = f_speed;
}

void Meteor::setDelta(float f_delta)
{
    delta = f_delta;
}

void Meteor::setDirection(int x, int y)
{
    speed_x = std::abs(speed_x);
    speed_y = std::abs(speed_y);

    //reset direction
    speed_x = x > 5 ? -(speed_x) : speed_x;
    speed_y = y > 5 ? -(speed_y) : speed_y;
}

/* get velocity */
float Meteor::getVelocity()
{
    return (speed * steps) * delta;
}

float Meteor::getxVelocity()
{
    return (speed_x * speed_s) * delta;
}

float Meteor::getyVelocity()
{
    return (speed_y * speed_s) * delta;
}

void Meteor::grow(float delta)
{
    //delta time
    setDelta(delta);

    //actual speed when calculated w/ the delta time
    float velocity = getVelocity();

    //grow meteor based off actual velocity amount
    addDims(velocity, velocity);
}

void Meteor::move(float delta)
{
    //delta time
    setDelta(delta);

    f_x += getxVelocity();
    f_y += getyVelocity();

    dst.x = (int) f_x;
    dst.y = (int) f_y;

    //outside of window
    if(f_x < 0) {
        speed_x = -(speed_x);
    }

    if(f_x + f_width > Game::getWidth()) {
        speed_x = -(speed_x);
    }

    //outside of window
    if(f_y < 0) {
        speed_y = -(speed_y);
    }

    if(f_y + f_height > Game::getHeight()) {
        speed_y = -(speed_y);
    }
}