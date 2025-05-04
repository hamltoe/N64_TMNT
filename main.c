#include <libdragon.h>
#include "World.h"
#include "Scenes/Scene_DEMO.h"
#include "Scenes/SceneS.h"

// === Global ECS Context ===
static World world;

void init_libdragon() {
    debug_init_isviewer();
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    joypad_init();
    timer_init();
    dfs_init(DFS_DEFAULT_LOCATION);
}

void init_component_pools(World* world) {
    component_pool_init(&world->transformPool, sizeof(TransformComponent));
    component_pool_init(&world->cameraPool, sizeof(CameraComponent));
    component_pool_init(&world->inputPool, sizeof(ControllerInput));
    component_pool_init(&world->animPool, sizeof(AnimationComponent));
    component_pool_init(&world->lightPool, sizeof(LightComponent));
    component_pool_init(&world->scenePool, sizeof(SceneComponent));

    world_register_pool(world, &world->inputPool);      // InputSystem
    world_register_pool(world, &world->transformPool);  // MovementSystem
    world_register_pool(world, &world->transformPool);  // TransformSystem
    world_register_pool(world, &world->cameraPool);     // CameraSystem
    world_register_pool(world, &world->animPool);       // AnimationSystem
    world_register_pool(world, &world->lightPool);      // RenderSystem
}

int main(void) {
    init_libdragon();
    systems_manager_init(&world.systems);
    init_component_pools(&world);

    scene_load_demo(&world);  // World passed explicitly

    while (1) {
        float deltaTime = (float)timer_ticks_to_ms(timer_read()) * 0.001f;
        systems_manager_update(&world.systems, deltaTime, world.poolList);
        timer_wait(16);
    }

    return 0;
}
