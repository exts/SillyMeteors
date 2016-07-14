//game
#include "LevelScene.hpp"

//std

//set default static value of the starting level
int LevelScene::level = 1;

LevelScene::~LevelScene(){}

//setup static function to set the current level
void LevelScene::setLevel(int level)
{
    LevelScene::level = level;
}

//setup static function to get the current level
int LevelScene::getLevel()
{
    return LevelScene::level;
}

//load assets
void LevelScene::load(SDL_Renderer *renderer)
{
    std::cout << "Level scene loaded..." << std::endl;

    //setup score font
    level_font = std::unique_ptr<Font>(
        new Font("assets/fonts/minecraftia.ttf", 60)
    );

    level_text_font = std::unique_ptr<Font>(
        new Font("assets/fonts/minecraftia.ttf", 40)
    );

    background = std::unique_ptr<Sprite>(
        new Sprite(renderer, "assets/background.png", 1280, 800)
    );

}

//manage events
void LevelScene::events(SDL_Event e)
{
    //Start level
    if(e.type == SDL_MOUSEBUTTONDOWN
        && e.button.x >= 0 && e.button.x <= Game::getWidth()
        && e.button.y >= 0 && e.button.y <= Game::getHeight()) {
        SceneManager::setScene("GameScene");
    }
}

//update data
void LevelScene::update(float delta)
{

}

void LevelScene::draw(SDL_Renderer *renderer)
{
    SDL_Rect pos = background->pos;

    SDL_RenderCopy(renderer, background->texture.get(), NULL, &pos);

    drawLevel(renderer);
}

void LevelScene::drawLevel(SDL_Renderer *renderer)
{
    //font colors
    SDL_Color white_font = {255, 255, 255, 255};

    //level text
    std::string level_text1 = "Level";

    //current level
    std::ostringstream olevel_text;
    olevel_text << getLevel();
    std::string level_text2 = olevel_text.str();

    //draw font
    level_text_font->draw(level_text1, renderer, white_font, 0, -100, 1, 1);
    level_font->draw(level_text2, renderer, white_font, 0, 0, 1, 1);
}