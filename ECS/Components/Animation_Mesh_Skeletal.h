#pragma once
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
#include <stdbool.h>

typedef struct {
    T3DAnim idle;
    T3DAnim walk;
    T3DAnim attack;

    T3DSkeleton* skeleton;
    T3DSkeleton* blendSkeleton;

    bool isAttacking;
    bool attackPlayed;

    float blendFactor;
    float walkSpeed;
} AnimationComponent;

