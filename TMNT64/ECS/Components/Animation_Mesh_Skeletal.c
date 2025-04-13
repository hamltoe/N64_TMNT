#include "ecs/Components/Animation_Mesh_Skeletal.h"
#include "ecs/ComponentManager.h"
#include <libdragon.h>
#include <malloc.h>

extern T3DModel* model; // optionally pass model if not global

void animation_component_spawn(ComponentPool* animPool, EntityID id) {
    T3DSkeleton* skeleton = malloc_uncached(sizeof(T3DSkeleton));
    *skeleton = t3d_skeleton_create(model);

    T3DSkeleton* blendSkeleton = malloc_uncached(sizeof(T3DSkeleton));
    *blendSkeleton = t3d_skeleton_clone(skeleton, false);

    AnimationComponent anim = {
        .idle = t3d_anim_create(model, "Snake_Idle"),
        .walk = t3d_anim_create(model, "Snake_Walk"),
        .attack = t3d_anim_create(model, "Snake_Attack"),
        .skeleton = skeleton,
        .blendSkeleton = blendSkeleton,
        .isAttacking = false,
        .attackPlayed = false,
        .blendFactor = 0.0f,
        .walkSpeed = 1.0f,
    };

    t3d_anim_attach(&anim.idle, skeleton);
    t3d_anim_attach(&anim.walk, blendSkeleton);
    t3d_anim_attach(&anim.attack, skeleton);
    t3d_anim_set_looping(&anim.attack, false);
    t3d_anim_set_playing(&anim.attack, false);

    component_pool_add(animPool, &anim);
}

void RenderSystem(ComponentPool* pool, float deltaTime) {
    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    t3d_screen_clear_color(RGBA32(224, 180, 96, 0xFF));
    t3d_screen_clear_depth();

    T3DVec3 lightDirVec = {{1.0f, 1.0f, 1.0f}};
    t3d_vec3_norm(&lightDirVec);
    uint8_t colorAmbient[4] = {0xAA, 0xAA, 0xAA, 0xFF};
    uint8_t colorDir[4]     = {0xFF, 0xAA, 0xAA, 0xFF};

    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_directional(0, colorDir, &lightDirVec);
    t3d_light_set_count(1);

    // Draw the map
    t3d_matrix_push(mapMatFP);
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
    t3d_model_draw(modelMap);
    t3d_matrix_pop(1);

    // Draw all animated characters
    for (int i = 0; i < pool->count; i++) {
        AnimationComponent* anim = (AnimationComponent*)pool->components[i];

        t3d_matrix_push(modelMatFP); // assumes modelMatFP is set externally
        rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        t3d_model_draw_skinned(model, anim->skeleton); // model is currently global
        t3d_matrix_pop(1);

        // Optionally: draw shadow model too
        t3d_matrix_push(modelMatFP);
        rdpq_set_prim_color(RGBA32(0, 0, 0, 120));
        t3d_model_draw(modelShadow);
        t3d_matrix_pop(1);
    }

    rdpq_detach_show();
}
