#include "scene.h"
#include "libdragon.h"
#include "t3d/t3d.h"

void SceneSystem(ComponentPool* pool, float deltaTime) {
    for (int i = 0; i < pool->count; i++) {
        SceneComponent* scene = (SceneComponent*)pool->components[i];

        if (scene->isTransitioning) {
            // Handle unloading old scene / cleanup here

            scene->currentScene = scene->nextScene;
            scene->isTransitioning = false;

            // Handle scene-specific setup
            switch (scene->currentScene) {
            case SCENE_MENU:
                // load_menu_assets();
                break;
            case SCENE_GAME:
                // load_game_assets();
                break;
            case SCENE_PAUSE:
                // freeze gameplay, show pause overlay
                break;
            case SCENE_CUTSCENE:
                // prepare camera or UI overlays
                break;
            default:
                break;
            }
        }
    }
}
