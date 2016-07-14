#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "base.hpp"

int Base::s_width = 0;
int Base::s_height = 0;
int Base::o_width = 0;
int Base::o_height = 0;
bool Base::running = true;

Base::~Base()
{
    cleanUp();
}

int Base::getWidth()
{
    return s_width;
}

int Base::getHeight()
{
    return s_height;
}

float Base::getWidthRatio()
{
    // std::cout << o_width << ", " << o_height << std::endl;
    return (float) s_width / o_width;
}

float Base::getHeightRatio()
{

    // std::cout << old_ratio_height << ", " << new_ratio_height << std::endl;
    // std::cout << old_ratio_height << ", " << new_ratio_height << std::endl;

    return (float) s_height / o_height;
}

void Base::stop()
{
    running = false;
}

void Base::setOriginalSize(int w_width, int w_height)
{
    o_width = w_width;
    o_height = w_height;
    // std::cout << o_width << ", " << o_height << std::endl;
}

/**
 * Used to setup our basic game
 */

void Base::setup(std::string g_name, int g_width, int g_height)
{
    setup(g_name, g_width, g_height, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0);
}

void Base::setup(std::string g_name, int g_width, int g_height, int win_pos_x, int win_pos_y, int win_flags) 
{
    //window name
    name = g_name;

    //window dimensions
    s_width = width = g_width;
    s_height = height = g_height;

    //initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    //create window
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, win_flags);
    if(window == NULL) {
        std::cout << "Couldn' create SDL Window: " << SDL_GetError() << std::endl;
        return;
    }

    //create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL) {
        std::cout << "Couldn't load SDL Renderer: " << SDL_GetError() << std::endl;
        return;
    }

    //init fonts
    if(TTF_Init() == -1) {
        std::cout << "Couldn't Initiate TTF API: " << TTF_GetError() << std::endl;
        return;
    }

    //load assets
    loadAssets();

    //game loop
    loop();
}

void Base::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}

void Base::setFps(int fps_limit)
{
    //frames per second 
    fps = fps_limit;

    if(fps <= 0) {
        fps = 0;
        m_fps = 0;
        return;
    }

    //frames per milliseconds
    m_fps = 1000/fps;
}

void Base::limitFps()
{
    //don't cap fps
    if(fps <= 0)
        return;

    //cap fps 
    int current_speed = SDL_GetTicks() - current_frame_speed;
    if(m_fps > current_speed) {
        SDL_Delay(m_fps - current_speed);
    }
}

void Base::setDelta()
{
    //get frame ms
    setTicks();

    //get delta time
    delta_time = (float) (current_frame_speed - last_frame_speed) / 1000;
}

void Base::setTicks()
{
    //set last frame time    
    last_frame_speed = current_frame_speed;

    //set current frame
    current_frame_speed = SDL_GetTicks();
}

void Base::setTicks(bool skip)
{
    //don't set last frame
    if(skip != true) {
        last_frame_speed = current_frame_speed;
    }

    //set current frame
    current_frame_speed = SDL_GetTicks();
}

void Base::handleEvents()
{
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
        }
        events(event);
    }
}

//default draw method
void Base::draw()
{
    //clear renderer
    SDL_RenderClear(renderer);

    //update renderer
    SDL_RenderPresent(renderer);
}

void Base::loop()
{
    //start ticks
    setTicks(true);

    while(running) {

        //get delta time
        setDelta();

        //events
        handleEvents();

        //update
        update(delta_time);

        //draw
        draw();

        //lock fps
        limitFps();
    }
}

void Base::events(SDL_Event e)
{
}

void Base::update(float delta)
{
}

void Base::loadAssets()
{
}