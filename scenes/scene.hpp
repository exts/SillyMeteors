#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"
#include "SDL_image.h"

class Scene 
{
public:
    Scene(){}
    virtual ~Scene(){}
    virtual void load(SDL_Renderer *renderer) = 0;
    virtual void events(SDL_Event e) = 0;
    virtual void update(float delta) = 0;
    virtual void draw(SDL_Renderer *renderer) = 0;
};

#endif