#pragma once
#include <t3d/t3d.h>

typedef struct {
    T3DVec3 position;
    T3DVec3 target;
    T3DVec3 up;
    float fov;
    float nearPlane;
    float farPlane;
    bool isActive;
    T3DViewport viewport;
} CameraComponent;
