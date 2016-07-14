#include "game.hpp"

int main(int argc, char **argv)
{
    // {
        Game app = Game();
        app.setOriginalSize(1280, 800);
        app.setup("Silly Meteors", 1280, 800);
    // }

    // system("PAUSE");
    
    return 0;
}