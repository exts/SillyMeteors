//declaration
#include "GameScene.hpp"

//std


GameScene::~GameScene()
{
    std::cout << "Gamescene destructor" << std::endl;
}

void GameScene::load(SDL_Renderer *renderer)
{
    std::cout << "Game Scene Loaded" << std::endl;

    //setup score font
    score_font = std::unique_ptr<Font>(new Font("assets/fonts/minecraftia.ttf", 14));

    //big meteor 1
    sprites.add("mb1", new Sprite(renderer, "assets/mb1.png", 101, 84));

    //big meteor 2
    sprites.add("mb2", new Sprite(renderer, "assets/mb2.png", 120, 98));

    //big meteor 3
    sprites.add("mb3", new Sprite(renderer, "assets/mb3.png", 89, 82));

    //big meteor 1
    sprites.add("mb4", new Sprite(renderer, "assets/mb4.png", 98, 96));

    //medium meteor 1
    sprites.add("mm1", new Sprite(renderer, "assets/mm1.png", 98, 96));

    //medium meteor 2
    sprites.add("mm2", new Sprite(renderer, "assets/mm2.png", 43, 43));

    //small meteor 1
    sprites.add("ms1", new Sprite(renderer, "assets/ms1.png", 28, 28));

    //small meteor 2
    sprites.add("ms2", new Sprite(renderer, "assets/ms2.png", 29, 26));

    //tiny meteor 1
    sprites.add("mt1", new Sprite(renderer, "assets/mt1.png", 18, 18));

    //tiny meteor 2
    sprites.add("mt2", new Sprite(renderer, "assets/mt2.png", 16, 15));

    //create vector of all sprite names for 
    //random selection when creating random meteors
    for(auto &s_name : sprites.sprites) {
        sprite_names.push_back(s_name.first);
    }

    //randomly generate starting meteors
    addMeteors(meteor_start_count);
}

void GameScene::events(SDL_Event e)
{
    //mouse clicked
	if(e.type == SDL_MOUSEBUTTONDOWN) {
        mouse_down = true;
        mouse_x = e.button.x;
        mouse_y = e.button.y;
	}

	//android support
	if(e.type == SDL_FINGERDOWN) {
		mouse_down = true;
        // mouse_x = (int) e.tfinger.x;
        // mouse_y = (int) e.tfinger.y;
        mouse_x = (int) ( (float) e.tfinger.x * Game::getWidth() / 32678 );
		mouse_y = (int) ( (float) e.tfinger.y * Game::getHeight() / 32678 );
	}
}

void GameScene::update(float delta)
{

    //check current level
    checkLevel();

    //check if we need to go to a new level
    nextLevel();

    //check how many seconds passed
    if(secondsPassed(1, delta) && countdown > 0) {
        countdown -= 1;
    }

    //is the game over?
    if(meteors.size() > 0 && countdown <= 0) {
        SceneManager::setScene("GameoverScene");
        return;
    }

    //loop through each meteor and increase the size
    for(auto &meteor : meteors) {
        // meteor.grow(delta);
        meteor.move(delta);
    }

    //check if mouse button was pressed
    if(mouse_down) {

        //random number generation
        std::random_device r_device;
        std::mt19937 re(r_device());
        std::uniform_int_distribution<int> r_dist_meteors(1, 2);

        //check mouse click collision w/ meteors
        for(int x = 0; x < (int) meteors.size(); x++) {

            //check collision
            if(mouse_x >= meteors[x].getDims().x
                && mouse_x <= meteors[x].getDims().w + meteors[x].getDims().x
                && mouse_y >= meteors[x].getDims().y
                && mouse_y <= meteors[x].getDims().h + meteors[x].getDims().y) {

                //delete
                meteors.erase(meteors.begin()+x);

                ++points;
            }
        }
    }

    //force mouse click to be disabled after each frame so you can't
    //hold down and cheat the system lol
    mouse_down = false;
}

void GameScene::draw(SDL_Renderer *renderer)
{
    //draw score
    drawScore(renderer);

    //draw random meteors
    for(auto meteor : meteors) {
        meteor.draw(renderer);
    }
}

void GameScene::addMeteors(int count)
{
    //random number stuff? - I won't lie this shit's kind of over my head lol
    std::random_device r_device;
    std::mt19937 re(r_device());
    std::uniform_int_distribution<int> r_dist_speed(10, 30);
    std::uniform_int_distribution<int> r_dist_rnd_dir(1, 10);
    std::uniform_int_distribution<int> r_dist_win_pos_x(0, Game::getWidth());
    std::uniform_int_distribution<int> r_dist_win_pos_y(0, Game::getHeight());
    std::uniform_int_distribution<int> r_dist_sprite_name(0, (int) sprite_names.size()-1);

    //randomly generate starting meteors
    for(int x = 0; x < count; x++) {

        //select random meteor
        int rm_name = r_dist_sprite_name(re);
        Meteor random_meteor(sprite_names[rm_name], &sprites);

        //set random direction
        random_meteor.setDirection(r_dist_rnd_dir(re), r_dist_rnd_dir(re));

        //select random x position
        int rp_x = r_dist_win_pos_x(re);

        if(rp_x < 0) {
            rp_x = 0;
        }

        if(rp_x + random_meteor.getDims().w > Game::getWidth()) {
            rp_x = Game::getWidth() - random_meteor.getDims().w;
        }

        //select random y position
        int rp_y = r_dist_win_pos_y(re);

        if(rp_y < (0 + window_height_top_padding)) {
            rp_y = 0 + window_height_top_padding;
        }

        if(rp_y + random_meteor.getDims().h > Game::getHeight()) {
            rp_y = Game::getHeight() - random_meteor.getDims().h;
        }

        //set random meteor position
        random_meteor.setPosition(rp_x, rp_y);

        //set random speed
        // random_meteor.setSpeed((float) r_dist_speed(re));
        random_meteor.setSpeedX((float) r_dist_speed(re));
        random_meteor.setSpeedY((float) r_dist_speed(re));

        if(x % 20 == 0) {
            random_meteor.setSpeed(10);
        }

        //add meteor to meteors vector
        meteors.push_back(
            random_meteor
        );
    }
}

void GameScene::drawScore(SDL_Renderer *renderer)
{
    //setup score string
    std::ostringstream score;
    score << "Time left: " << countdown;
    std::string s_score = score.str();
    
    SDL_Color white_font = {255, 255, 255, 255};

    score_font->draw(s_score, renderer, white_font, 10, 4, 0, 0);
}

bool GameScene::secondsPassed(int seconds, float delta)
{
    //track time between frames every frame
    current_time += delta;

    //convert float to int to get exact second
    int sec_passed = (int) current_time;

    //check if time collected has hit 1 second
    if(sec_passed == seconds) {
        current_time = 0.0f;
        return true;
    }

    return false;
}

void GameScene::checkLevel()
{
    if(current_level != LevelScene::getLevel()) {
        //set current level
        current_level = LevelScene::getLevel();

        //reset meteors count
        meteors.clear();

        //add more meteors...
        addMeteors(current_level * meteor_start_count);

        //bonus time
        int added_time = 0;

        if(countdown >= 5) {
            added_time = 5;
        }

        if(countdown >= 10) {
            added_time = 10;
        }

        if(countdown >= 20) {
            added_time = 15;
        }

        //add time to the clock
        if(current_level > 1) {
            countdown += added_time;
        }
    }
}

void GameScene::nextLevel()
{
    if(meteors.size() <= 0 && countdown > 0) {
        LevelScene::setLevel(LevelScene::getLevel() + 1);
        SceneManager::setScene("LevelScene");
    }
}