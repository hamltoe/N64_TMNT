#pragma once
#include <t3d/t3d.h>

typedef enum {
    LIGHT_TYPE_AMBIENT,
    LIGHT_TYPE_DIRECTIONAL
} LightType;

typedef struct {
    LightType type;
    T3DVec3 direction;     // Only used for directional lights
    uint8_t color[4];      // RGBA color
    bool isActive;
} LightComponent;
