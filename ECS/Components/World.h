#pragma once

#include "ecs/SystemsManager.h"
#include "ecs/ComponentsManager.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Controller.h"
#include "Components/Animation_Mesh_Skeletal.h"
#include "Components/Light.h"
#include "Components/Scene.h"

typedef enum {
    POOL_TRANSFORM,
    POOL_CAMERA,
    POOL_INPUT,
    POOL_ANIMATION,
    POOL_LIGHT,
    POOL_SCENE,
    POOL_COUNT
} ComponentPoolType;

typedef struct {
    SystemsManager systems;
    ComponentPool pools[POOL_COUNT];
    ComponentPool* poolList[MAX_WORLD_POOLS];
    uint8_t poolCount;
} World;

static inline void world_register_pool(World* world, ComponentPoolType type, size_t size) {
    component_pool_init(&world->pools[type], size);
    if (world->poolCount < MAX_WORLD_POOLS) {
        world->poolList[world->poolCount++] = &world->pools[type];
    }
}

static inline ComponentPool* world_get_pool(World* world, ComponentPoolType type) {
    return &world->pools[type];
}
