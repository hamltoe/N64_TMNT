#pragma once
#include <stdbool.h>
#include "ComponentPool.h"


typedef enum {
    SCENE_START,
    SCENE_MENU,
    SCENE_GAME,
    SCENE_PAUSE,
    SCENE_CUTSCENE,
    SCENE_DEBUG,
    // Add more scenes here
} SceneType;

typedef struct {
    SceneType currentScene;
    SceneType nextScene;
    bool isTransitioning;
} SceneComponent;

void SceneSystem(ComponentPool* pool, float deltaTime);
