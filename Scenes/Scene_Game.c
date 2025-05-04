#include "Scene_Game.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Controller.h"
#include "Components/Animation_Mesh_Skeletal.h"
#include "Components/Scene.h"
#include "World.h"
#include "t3d/t3d.h"

extern World world;
extern T3DViewport viewport;

static void register_gameplay_systems(World* world) {
    world_register_pool(world, &world->inputPool);
    world_register_pool(world, &world->transformPool);  // MovementSystem
    world_register_pool(world, &world->transformPool);  // TransformSystem
    world_register_pool(world, &world->cameraPool);
    world_register_pool(world, &world->animPool);
    world_register_pool(world, &world->lightPool);
}

void load_game_scene(void) {
    EntityID player = { .ID = 1, .instanceIndex = 0 };

    controller_component_spawn(&world.inputPool, INPUT_SOURCE_PLAYER, player);
    animation_component_spawn(&world.animPool, player);

    TransformComponent transform = {
        .position = {{0, 0.15f, 0}},
        .rotation = {{0, 0, 0}},
        .scale    = {{0.125f, 0.125f, 0.125f}},
    };
    component_pool_add(&world.transformPool, &transform);

    CameraComponent cam = {
        .position    = {{0, 45, 80}},
        .target      = {{0, 0, -10}},
        .up          = {{0, 1, 0}},
        .fov         = T3D_DEG_TO_RAD(85.0f),
        .nearPlane   = 10.0f,
        .farPlane    = 150.0f,
        .isActive    = true,
        .viewport    = viewport
    };
    component_pool_add(&world.cameraPool, &cam);

    SceneComponent scene = {
        .currentScene = SCENE_GAME,
        .nextScene = SCENE_GAME,
        .isTransitioning = false
    };
    component_pool_add(&world.scenePool, &scene);

    register_gameplay_systems(&world);
}
