#pragma once

typedef enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_PAUSE,
    SCENE_START,
    SCENE_CUTSCENE,
    SCENE_DEBUG
} SceneType;

typedef enum {
    TRANSITION_NONE,
    TRANSITION_FADE_OUT,
    TRANSITION_LOADING,
    TRANSITION_FADE_IN
} SceneTransitionState;

typedef struct {
    SceneType currentScene;
    SceneType nextScene;
    bool isTransitioning;
    SceneTransitionState transitionState;
    float transitionTimer;
    float fadeDuration;
    float fadeAlpha;  // 0 = transparent, 1 = black
} SceneComponent;

typedef struct Scene {
    void (*init)(void);
    void (*update)(float deltaTime);
    void (*draw)(void);
    void (*unload)(void);
} Scene;

typedef struct {
    Scene* current;
    Scene* next;
    bool transition;
} SceneManager;

SceneManager sceneManager;
