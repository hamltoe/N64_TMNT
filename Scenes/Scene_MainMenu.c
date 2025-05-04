#include "Scene_Menu.h"
#include "Components/Camera.h"
#include "Components/Scene.h"
#include "World.h"
#include "t3d/t3d.h"

extern World world;
extern T3DViewport viewport;

static void register_menu_systems(World* world) {
    world_register_pool(world, &world->cameraPool);
    world_register_pool(world, &world->scenePool);
}

void load_menu_scene(void) {
    CameraComponent cam = {
        .position    = {{0, 0, 60}},
        .target      = {{0, 0, 0}},
        .up          = {{0, 1, 0}},
        .fov         = T3D_DEG_TO_RAD(70.0f),
        .nearPlane   = 10.0f,
        .farPlane    = 150.0f,
        .isActive    = true,
        .viewport    = viewport
    };
    component_pool_add(&world.cameraPool, &cam);

    SceneComponent scene = {
        .currentScene = SCENE_MENU,
        .nextScene = SCENE_MENU,
        .isTransitioning = false
    };
    component_pool_add(&world.scenePool, &scene);

    register_menu_systems(&world);
}
