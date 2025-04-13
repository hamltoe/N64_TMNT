#pragma once

#include "ECS/ComponentManager.h"
#include "Components/Component.h"

typedef void (*SystemFunc)(ComponentPool** pools, float deltaTime);

typedef struct {
    SystemFunc run;
} System;
