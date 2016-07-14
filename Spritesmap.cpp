//game
#include "spritesmap.hpp"

void Spritesmap::add(std::string name, Sprite *sprite)
{
    sprites.insert(std::make_pair(name, 
        std::unique_ptr<Sprite>(sprite)
    ));
}

Sprite *Spritesmap::get(std::string name)
{
    return sprites[name].get();
}