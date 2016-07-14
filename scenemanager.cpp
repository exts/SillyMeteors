//include class definitions
#include "scenemanager.hpp"

//include scenes
#include "scenes/GameScene.hpp"
#include "scenes/LevelScene.hpp"
#include "scenes/GameoverScene.hpp"

//static scene instance
std::string SceneManager::current_scene = std::string();

void SceneManager::setup(SDL_Renderer *renderer)
{
    //add scenes
    addScene("GameScene", new GameScene());
    addScene("LevelScene", new LevelScene());
    addScene("GameoverScene", new GameoverScene());

    //set start scene
    setScene("LevelScene");

    //don't want to do anything crazy
    if(!currentSceneExists()) {
        return;
    }

    //loop through every loaded scene and load their assets
    //into memory so we can call this function only once.
	for(auto &c_scene : scenes) {
		c_scene.second->load(renderer);
	}
}

/**
 * Add Scene to scenes array
 */
void SceneManager::addScene(std::string name, Scene *pScene)
{
    //add scene to maps array, spread it out to be more readible
    scenes.insert(
        std::make_pair(
            name,
            std::unique_ptr<Scene>(std::move(pScene))
        )
    );
}

/**
 * Draw scene to the main renderer
 */
void SceneManager::draw(SDL_Renderer *renderer)
{
    if(currentSceneExists()) {
        scenes[current_scene]->draw(renderer);
    }
}

/**
 * Update scene data every frame refresh
 * so if we need to change position do so here
 */
void SceneManager::update(float delta = 0.0f)
{
    if(currentSceneExists()) {
        scenes[current_scene]->update(delta);
    }
}

/**
 * Load scene specific settings here, this might allow
 * us to have scene specific keybindings in future projects
 */
void SceneManager::events(SDL_Event e)
{
    if(currentSceneExists()) {
        scenes[current_scene]->events(e);
    }
}

/**
 * Check if the current scene exists or
 * if the current scenes array is empty
 */
bool SceneManager::currentSceneExists()
{
    if(!scenes.empty() && scenes.count(current_scene) != 0) {
        return true;
    }

    return false;
}

/**
 * Set the static scene name so it can be called from
 * other scenes allowing us to change scenes
 */
void SceneManager::setScene(std::string scene_name)
{
    current_scene = scene_name;
}