
#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "Components/Component.h"

#define MAX_COMPONENTS 64

typedef struct {
    void* components[MAX_COMPONENTS];
    size_t size;
    uint8_t count;
} ComponentPool;

static inline void component_pool_init(ComponentPool* pool, size_t componentSize) {
    pool->size = componentSize;
    pool->count = 0;
    memset(pool->components, 0, sizeof(pool->components));
}

static inline void* component_pool_add(ComponentPool* pool, void* componentData) {
    if (pool->count >= MAX_COMPONENTS) return NULL;
    void* slot = malloc(pool->size);  // Swap to fixed buffer if needed
    memcpy(slot, componentData, pool->size);
    pool->components[pool->count++] = slot;
    return slot;
}
