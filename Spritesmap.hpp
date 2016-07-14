#ifndef SPRITESMAP_H
#define SPRITESMAP_H

//game
#include "sprite.hpp"

//std
#include <map>
#include <string>
#include <memory>

class Spritesmap
{

public:

    std::map<std::string, std::unique_ptr<Sprite>> sprites;
    Spritesmap(){}

    Sprite* get(std::string name);
    void add(std::string name, Sprite * sprite);
};

#endif