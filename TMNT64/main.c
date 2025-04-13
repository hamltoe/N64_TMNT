#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>
#include <t3d/t3ddebug.h>

#include "ECS/Components/DisplaySettings.h"
#include "ECS/ComponentsManager.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Controller.h"
#include "ECS/Components/Animation_Mesh_Skeletal.h"
#include "ECS/Components/Controller.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Camera.h"

float get_time_s() {
    return (float)((double)get_ticks_us() / 1000000.0);
}

T3DViewport viewport;


void MovementSystem(ComponentPool* pool, float deltaTime) {
    // Stub: apply input to transform and animation states
}

void RenderSystem(ComponentPool* pool, float deltaTime) {
    // Stub: draw model using current skeleton pose
}

int main(void) {
    debug_init_isviewer();
    debug_init_usblog();
    asset_init_compression(2);

    dfs_init(DFS_DEFAULT_LOCATION);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

    rdpq_init();
    joypad_init();

    t3d_init((T3DInitParams){});
    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));
    viewport = t3d_viewport_create();

    modelMatFP = malloc_uncached(sizeof(T3DMat4FP));
    mapMatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(mapMatFP, (float[3]){0.3f, 0.3f, 0.3f}, (float[3]){0, 0, 0}, (float[3]){0, 0, -10});

    modelMap = t3d_model_load("rom:/map.t3dm");
    modelShadow = t3d_model_load("rom:/shadow.t3dm");
    model = t3d_model_load("rom:/snake.t3dm");

    // === ECS Init ===
    SystemsManager systems;
    systems_manager_init(&systems);
    ComponentPool inputPool;
    component_pool_init(&inputPool, sizeof(ControllerInput));
    ComponentPool animPool;
    component_pool_init(&animPool, sizeof(AnimationComponent));
    ComponentPool transformPool;
    component_pool_init(&transformPool, sizeof(TransformComponent));
    TransformComponent transform = {
    .position = {{0, 0.15f, 0}},
    .rotation = {{0, 0, 0}},
    .scale = {{0.125f, 0.125f, 0.125f}},
    };
    component_pool_add(&transformPool, &transform);

    ComponentPool cameraPool;
    component_pool_init(&cameraPool, sizeof(CameraComponent));
    CameraComponent cam = {
        .position = {{0, 45, 80}},
        .target = {{0, 0, -10}},
        .up = {{0, 1, 0}},
        .fov = T3D_DEG_TO_RAD(85.0f),
        .nearPlane = 10.0f,
        .farPlane = 150.0f,
        .isActive = true,
        .viewport = viewport
    };
    component_pool_add(&cameraPool, &cam);


    systems_manager_add(&systems, InputSystem);
    systems_manager_add(&systems, AnimationSystem);
    systems_manager_add(&systems, MovementSystem);
    systems_manager_add(&systems, RenderSystem);

    ComponentPool* systemPools[MAX_SYSTEMS] = {
        &inputPool,
        &animPool,
        &transformPool,
        &cameraPool,
        NULL,
        NULL,
    };

    // Add a test entity with an AnimationComponent
    EntityID entity = { .ID = 1, .instanceIndex = 0 };
    animation_component_spawn(&animPool, entity);

    float lastTime = get_time_s() - (1.0f / 60.0f);


    while (true) {
        float now = get_time_s();
        float deltaTime = now - lastTime;
        lastTime = now;

        inputPool.count = 0;

        systems_manager_update(&systems, deltaTime, systemPools);

    }

    return 0;
}
