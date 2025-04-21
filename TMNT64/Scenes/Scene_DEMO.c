#include "Scenes/MyScene.h"
#include "ecs/SystemsManager.h"
#include "ecs/ComponentsManager.h"

#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Controller.h"
#include "Components/Animation_Mesh_Skeletal.h"
#include "Components/Light.h"

#include "ecs/Systems/CameraS.h"
#include "ecs/Systems/TransformS.h"
#include "ecs/Systems/ControllerS.h"
#include "ecs/Systems/RenderS.h"
#include "ecs/Systems/AnimationS.h"  // stub if not yet implemented
#include "ecs/Systems/LightingS.h"   // stub if not yet implemented

// External managers and component pools defined in main.c
extern SystemsManager systems;

extern ComponentPool transformPool;
extern ComponentPool cameraPool;
extern ComponentPool inputPool;
extern ComponentPool animPool;
extern ComponentPool lightPool;

void scene_load_demo(void) {
    // === Initialize persistent render data ===
    RenderSystem_Init();

    // === Register ECS systems in update order ===
    systems_manager_add(&systems, (SystemFunc)InputSystem);
    systems_manager_add(&systems, (SystemFunc)MovementSystem);  // depends on Input + Transform
    systems_manager_add(&systems, (SystemFunc)TransformSystem); // updates matrix
    systems_manager_add(&systems, (SystemFunc)CameraSystem);    // updates viewport
    systems_manager_add(&systems, (SystemFunc)AnimationSystem); // updates skeleton
    systems_manager_add(&systems, (SystemFunc)RenderSystem);    // draws everything

    // === Setup Player Entity ===
    TransformComponent playerTransform = {
        .position = {{0.0f, 0.15f, 0.0f}},
        .rotation = {{0.0f, 0.0f, 0.0f}},
        .scale = {{0.125f, 0.125f, 0.125f}},
    };
    component_pool_add(&transformPool, &playerTransform);

    ControllerInput playerInput = {
        .source = INPUT_SOURCE_PLAYER,
        .state = {0}
    };
    component_pool_add(&inputPool, &playerInput);

    AnimationComponent playerAnim = {
        .skeleton = t3d_skeleton_create(t3d_model_load("rom:/snake.t3dm"))  // assumes same model name
    };
    component_pool_add(&animPool, &playerAnim);

    // === Setup Camera ===
    CameraComponent camera = {
        .position = {{0.0f, 45.0f, 65.0f}},
        .target = {{0.0f, 0.0f, -10.0f}},
        .up = {{0.0f, 1.0f, 0.0f}},
        .fov = T3D_DEG_TO_RAD(85.0f),
        .nearPlane = 10.0f,
        .farPlane = 150.0f,
        .isActive = true,
        .viewport = t3d_viewport_create()
    };
    component_pool_add(&cameraPool, &camera);

    // === Setup Light ===
    LightComponent light = {
        .type = LIGHT_TYPE_DIRECTIONAL,
        .color = {0xFF, 0xAA, 0xAA, 0xFF},
        .direction = {{1.0f, 1.0f, 1.0f}},
        .isActive = true
    };
    component_pool_add(&lightPool, &light);
}
