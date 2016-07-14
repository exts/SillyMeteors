#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "scenes/scene.hpp"

class SceneManager
{
    //stores all our available scenes
    std::map<std::string, std::unique_ptr<Scene>> scenes;

    //current scene
    static std::string current_scene;


public:

    void setup(SDL_Renderer *renderer);
    bool currentSceneExists();
    void addScene(std::string name, Scene *pScene);

    void update(float delta);
    void events(SDL_Event e);
    void draw(SDL_Renderer *renderer);

    static void setScene(std::string scene_name);
};

#endif
