#include <t3d/t3d.h>
#include <stdbool.h>


typedef struct {
    T3DModel* model;
    T3DModel* shadow;
    bool isAnimated;
} ModelComponent;

