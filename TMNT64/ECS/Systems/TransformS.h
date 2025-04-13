#include <t3d/t3d.h>

typedef struct {
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
    T3DMat4FP matrix;
} TransformComponent;


void MovementSystem(ComponentPool* pool, float deltaTime);

void transform_move_forward(TransformComponent* transform, float distance);

void TransformSystem(ComponentPool* pool, float deltaTime);
