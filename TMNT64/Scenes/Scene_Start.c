#include "MyScene.h"
#include "ecs/SystemsManager.h"
#include "ecs/ComponentsManager.h"

#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Controller.h"
#include "Components/Animation_Mesh_Skeletal.h" // you referenced AnimationComponent
#include "Components/Light.h"

#include "ecs/Systems/CameraS.h"
#include "ecs/Systems/TransformS.h"
#include "ecs/Systems/ControllerS.h"
#include "ecs/Systems/RenderS.h"
#include "ecs/Systems/AnimationS.h" // assumed
#include "ecs/Systems/LightingS.h"  // assumed

extern SystemsManager systems;
extern ComponentPool transformPool;
extern ComponentPool cameraPool;
extern ComponentPool inputPool;
extern ComponentPool animPool;
extern ComponentPool lightPool;

void scene_load_demo(void) {
    RenderSystem_Init();

    // Initialize systems
    systems_manager_add(&systems, (SystemFunc)InputSystem);
    systems_manager_add(&systems, (SystemFunc)MovementSystem); // uses Input + Transform
    systems_manager_add(&systems, (SystemFunc)TransformSystem);
    systems_manager_add(&systems, (SystemFunc)CameraSystem);
    systems_manager_add(&systems, (SystemFunc)AnimationSystem);
    systems_manager_add(&systems, (SystemFunc)RenderSystem);

    // === Setup a player entity === //
    TransformComponent playerTransform = {
        .position = {{0, 0.15f, 0}},
        .rotation = {{0, 0, 0}},
        .scale = {{0.125f, 0.125f, 0.125f}},
    };
    component_pool_add(&transformPool, &playerTransform);

    ControllerInput playerInput = {
        .source = INPUT_SOURCE_PLAYER,
        .state = {0}
    };
    component_pool_add(&inputPool, &playerInput);

    AnimationComponent playerAnim = {
        .skeleton = t3d_skeleton_create(t3d_model_load("rom:/snake.t3dm"))
    };
    component_pool_add(&animPool, &playerAnim);

    // === Setup camera === //
    CameraComponent camera = {
        .position = {{0, 45, 65}},
        .target = {{0, 0, -10}},
        .up = {{0, 1, 0}},
        .fov = T3D_DEG_TO_RAD(85.0f),
        .nearPlane = 10.0f,
        .farPlane = 150.0f,
        .isActive = true,
        .viewport = t3d_viewport_create()
    };
    component_pool_add(&cameraPool, &camera);

    // === Setup a directional light === //
    LightComponent light = {
        .type = LIGHT_TYPE_DIRECTIONAL,
        .color = {0xFF, 0xAA, 0xAA, 0xFF},
        .direction = {{1.0f, 1.0f, 1.0f}},
        .isActive = true
    };
    component_pool_add(&lightPool, &light);
}
