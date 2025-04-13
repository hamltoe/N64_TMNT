#pragma once

typedef enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_PAUSE,
    SCENE_CUTSCENE,
    SCENE_DEBUG
} SceneType;

typedef struct {
    SceneType currentScene;
    SceneType nextScene;
    bool isTransitioning;
} SceneComponent;
