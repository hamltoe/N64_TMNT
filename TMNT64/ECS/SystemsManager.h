#pragma once

#include <stdint.h>
#include <stddef.h>
#include "ECS/Systems/System.h"  // defines System and SystemFunc

#define MAX_SYSTEMS 16

typedef struct {
    System systems[MAX_SYSTEMS];
    uint8_t count;
} SystemsManager;

/**
 * Initializes the systems manager.
 */
static inline void systems_manager_init(SystemsManager* manager) {
    manager->count = 0;
}

/**
 * Registers a new system to be updated each frame.
 * Returns 0 on success, -1 if the list is full.
 */
static inline int systems_manager_add(SystemsManager* manager, SystemFunc func) {
    if (manager->count >= MAX_SYSTEMS) return -1;
    manager->systems[manager->count++] = (System){ .run = func };
    return 0;
}

/**
 * Updates all registered systems with the given delta time.
 */
static inline void systems_manager_update(SystemsManager* manager, float deltaTime, ComponentPool** pools) {
    for (uint8_t i = 0; i < manager->count; ++i) {
        manager->systems[i].run(pools[i], deltaTime);
    }
}