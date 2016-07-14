//game
#include "gameoverscene.hpp"

//deconstruct
GameoverScene::~GameoverScene(){}

void GameoverScene::load(SDL_Renderer *renderer)
{
    //load font
    go_text = font_ptr(new Font("assets/fonts/minecraftia.ttf", 60));
    lvl_text = font_ptr(new Font("assets/fonts/minecraftia.ttf", 16));

    std::cout << "Gameover scene loaded" << std::endl;
}

void GameoverScene::events(SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN
        || e.type == SDL_FINGERDOWN) {
        Game::stop();
    }
}

void GameoverScene::update(float delta)
{

}

void GameoverScene::draw(SDL_Renderer *renderer)
{

    int levels = LevelScene::getLevel();

    std::ostringstream score;
    score << "You've completed " << levels;

    if(levels == 1) {
        score << " level";
    } else {
        score << " levels";
    }

    std::string s_score = score.str();

    go_text->draw("Game Over", renderer, {255, 255, 255, 255}, 0, 0, 1, 1);
    lvl_text->draw(s_score, renderer, {255, 255, 255, 255}, 0, 300, 1, 1);
    lvl_text->draw("[Press to Exit]", renderer, {255, 255, 255, 255}, 0, 100, 1, 1);
}