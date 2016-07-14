#include "SDL.h"
#include "SDL_image.h"

#include "game.hpp"

void Game::loadAssets()
{
    //load & setup scenes
    m_scenes.setup(renderer);
}

void Game::events(SDL_Event e)
{
    m_scenes.events(e);
}

void Game::update(float delta)
{
    m_scenes.update(delta);
}

void Game::draw()
{
    //clear renderer
    SDL_RenderClear(renderer);

    //draw scene stuff here
    m_scenes.draw(renderer);

    //update renderer
    SDL_RenderPresent(renderer);
}