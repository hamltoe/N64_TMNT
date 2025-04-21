#include "SceneS.h"


void load_scene_menu(ComponentPool* scenePool) {
    // Example: Set up camera position, background, UI models, etc.
}


void load_scene_game(ComponentPool* scenePool, ComponentPool* animPool, ComponentPool* transformPool, EntityID entity) {
    // Set up the animated player
    animation_component_spawn(animPool, entity);

    TransformComponent transform = {
        .position = {{0, 0.15f, 0}},
        .rotation = {{0, 0, 0}},
        .scale = {{0.125f, 0.125f, 0.125f}},
    };
    component_pool_add(transformPool, &transform);
}


void SceneSystem(ComponentPool** pools, float deltaTime) {
    ComponentPool* scenePool = pools[0];
    SceneComponent* scene = (SceneComponent*)scenePool->components[0];

    switch (scene->transitionState) {
    case TRANSITION_NONE:
        if (scene->currentScene != scene->nextScene) {
            scene->transitionState = TRANSITION_FADE_OUT;
            scene->transitionTimer = 0.0f;
            scene->fadeDuration = 1.0f;
        }
        break;

    case TRANSITION_FADE_OUT:
        scene->transitionTimer += deltaTime;
        scene->fadeAlpha = scene->transitionTimer / scene->fadeDuration;
        if (scene->fadeAlpha >= 1.0f) {
            scene->fadeAlpha = 1.0f;
            scene_on_exit(scene->currentScene);
            scene->currentScene = scene->nextScene;
            scene->transitionState = TRANSITION_LOADING;
            scene->transitionTimer = 0.0f;
        }
        break;

    case TRANSITION_LOADING:
        scene_on_enter(scene->currentScene);
        scene->transitionState = TRANSITION_FADE_IN;
        break;

    case TRANSITION_FADE_IN:
        scene->transitionTimer += deltaTime;
        scene->fadeAlpha = 1.0f - (scene->transitionTimer / scene->fadeDuration);
        if (scene->fadeAlpha <= 0.0f) {
            scene->fadeAlpha = 0.0f;
            scene->transitionState = TRANSITION_NONE;
        }
        break;
    }
}

void scene_switch(Scene* next) {
    sceneManager.next = next;
    sceneManager.transition = true;
}

void scene_on_enter(SceneType scene) {
    switch (scene) {
    case SCENE_MENU: /* spawn UI */ break;
    case SCENE_GAME: /* load game logic */ break;
    default: break;
    }
}

void scene_on_exit(SceneType scene) {
    switch (scene) {
    case SCENE_MENU: /* cleanup */ break;
    case SCENE_GAME: /* free models */ break;
    default: break;
    }
}



/*
//This is an example usage to call a scene change.
SceneComponent* scene = (SceneComponent*)scenePool->components[0];
if (input->state.button_start) {
    scene->nextScene = SCENE_GAME;
}
*/
