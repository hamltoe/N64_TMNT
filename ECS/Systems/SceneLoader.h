#pragma once
#include "ecds/Components/scene.h"

typedef struct {
    SceneType type;
    void (*load_func)(void);
} SceneModule;

// Called once at boot (to scan .scene_modules)
void scene_registry_init(void);

// Called when changing scenes
void load_scene(SceneType type);

// Required by SceneSystem
void unload_scene(SceneType scene);

// GCC section-based plugin registration
#define REGISTER_SCENE(type, func) \
    __attribute__((section(".scene_modules"))) \
    const SceneModule _scene_module_##type = { type, func };
