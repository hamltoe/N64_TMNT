#include "SceneS.h"

void SceneSystem(World* world, float deltaTime) {
    // Example hook: run scene update system here if you add a SceneComponent pool-based update
    (void)world;
    (void)deltaTime;
}

void scene_on_enter(SceneType scene) {
    // Custom logic for entering scenes
    (void)scene;
}

void scene_on_exit(SceneType scene) {
    // Custom logic for exiting scenes
    (void)scene;
}
