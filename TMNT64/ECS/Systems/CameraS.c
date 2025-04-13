#include "ecs/Systems/"


void CameraSystem(ComponentPool* pool, float deltaTime) {
    for (int i = 0; i < pool->count; i++) {
        CameraComponent* cam = (CameraComponent*)pool->components[i];
        if (!cam->isActive) continue;

        t3d_viewport_set_projection(&cam->viewport, cam->fov, cam->nearPlane, cam->farPlane);
        t3d_viewport_look_at(&cam->viewport, &cam->position, &cam->target, &cam->up);
        t3d_viewport_attach(&cam->viewport); // attaches for next draw pass
    }
}
