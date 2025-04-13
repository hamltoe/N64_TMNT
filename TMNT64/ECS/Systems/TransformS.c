#include "Transform.h"
#include "TransformS.h"


void MovementSystem(ComponentPool** pools, float deltaTime) {
    ComponentPool* inputPool = pools[0];
    ComponentPool* transformPool = pools[1];

    if (inputPool->count != transformPool->count) return;

    static float rotY = 0.0f;
    static float currSpeed = 0.0f;
    static T3DVec3 moveDir = { {0, 0, 0} };

    for (int i = 0; i < transformPool->count; i++) {
        TransformComponent* transform = (TransformComponent*)transformPool->components[i];
        ControllerInput* input = (ControllerInput*)inputPool->components[i];

        T3DVec3 newDir = { {
            input->state.stick_x * 0.05f, 0,
           -input->state.stick_y * 0.05f
        } };
        float speed = sqrtf(t3d_vec3_len2(&newDir));

        if (speed > 0.15f) {
            newDir.v[0] /= speed;
            newDir.v[2] /= speed;
            moveDir = newDir;

            float newAngle = atan2f(moveDir.v[0], moveDir.v[2]);
            rotY = t3d_lerp_angle(rotY, newAngle, 0.25f);
            currSpeed = t3d_lerp(currSpeed, speed * 0.15f, 0.15f);
        }
        else {
            currSpeed *= 0.8f;
        }

        transform->position.v[0] += moveDir.v[0] * currSpeed;
        transform->position.v[2] += moveDir.v[2] * currSpeed;

        // Clamp inside box
        const float BOX_SIZE = 140.0f;
        for (int j = 0; j < 3; j++) {
            if (transform->position.v[j] < -BOX_SIZE) transform->position.v[j] = -BOX_SIZE;
            if (transform->position.v[j] > BOX_SIZE) transform->position.v[j] = BOX_SIZE;
        }

        transform->rotation.v[1] = -rotY;

        t3d_mat4fp_from_srt_euler(&transform->matrix,
            transform->scale.v,
            transform->rotation.v,
            transform->position.v
        );
    }
}




void transform_move_forward(TransformComponent* transform, float distance) {
    float yaw = transform->rotation.v[1]; // rotation around Y axis (in radians)

    float forwardX = sinf(yaw);
    float forwardZ = cosf(yaw);

    transform->position.v[0] += forwardX * distance;
    transform->position.v[2] += forwardZ * distance;
}

void TransformSystem(ComponentPool* pool, float deltaTime) {
    for (int i = 0; i < pool->count; ++i) {
        TransformComponent* t = (TransformComponent*)pool->components[i];

        // Example: move every transform forward 0.1 units per frame
        transform_move_forward(t, 0.1f * deltaTime);
    }
}

