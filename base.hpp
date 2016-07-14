#ifndef BASE_H
#define BASE_H

#include <string>

#include "SDL.h"
#include "SDL_image.h"

class Base
{
    //game name
    std::string name = std::string();

    //game dimensions
    int width = 0, height = 0;
    static int s_width, s_height;
    static int o_width, o_height;

    //fps/deltatime/ticks
    float delta_time = 0.0f;
    int fps = 0, m_fps = 0;
    int last_frame_speed = 0, current_frame_speed = 0;


public:

    //game running?
    static bool running;

    //sdl variables
    SDL_Event event;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Base(){}

    virtual ~Base();

    static int getWidth();
    static int getHeight();
    static float getWidthRatio();
    static float getHeightRatio();

    static void stop();

    virtual void cleanUp();
    virtual void handleEvents();
    virtual void setOriginalSize(int w_width, int w_height);
    virtual void setup(std::string g_name, int g_width, int g_height);
    virtual void setup(std::string g_name, int g_width, int g_height, int win_pos_x, int win_pos_y, int win_flags);

    virtual void draw();
    virtual void loop();
    virtual void loadAssets();
    virtual void events(SDL_Event e);
    virtual void update(float delta);

    virtual void limitFps();
    virtual void setDelta();
    virtual void setTicks();
    virtual void setTicks(bool skip);
    virtual void setFps(int fps_limit);
};

#endif