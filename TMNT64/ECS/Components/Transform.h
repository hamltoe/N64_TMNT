#pragma once
#include <t3d/t3dmath.h>  // for T3DVec3

typedef struct {
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
} TransformComponent;