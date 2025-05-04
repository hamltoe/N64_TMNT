#pragma once
#include <stdint.h>

typedef union {
    struct {
        uint8_t instanceIndex;
        uint8_t ID;
    };
    uint16_t entityID;
} EntityID;

#define NULL_ENTITY ((EntityID){ .entityID = 0 })