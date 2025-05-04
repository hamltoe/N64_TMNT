#include "RenderS.h"

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>

#include "ecs/Components/Animation_Mesh_Skeletal.h"  // your AnimationComponent

// Global rendering data
static T3DModel* model;
static T3DModel* modelMap;
static T3DModel* modelShadow;
static T3DMat4FP* modelMatFP;
static T3DMat4FP* mapMatFP;
static T3DViewport viewport;

void RenderSystem_Init(void) {
    modelMatFP = malloc_uncached(sizeof(T3DMat4FP));
    mapMatFP = malloc_uncached(sizeof(T3DMat4FP));
    modelMap = t3d_model_load("rom:/map.t3dm");
    modelShadow = t3d_model_load("rom:/shadow.t3dm");
    model = t3d_model_load("rom:/snake.t3dm");

    viewport = t3d_viewport_create();
    t3d_mat4fp_from_srt_euler(mapMatFP,
        (float[3]) {
        0.3f, 0.3f, 0.3f
    },
        (float[3]) {
        0, 0, 0
    },
        (float[3]) {
        0, 0, -10
    });
}

void RenderSystem(ComponentPool** pools, float deltaTime) {

    
    ComponentPool* animPool = pools[0];
    ComponentPool* transformPool = pools[1];
    ComponentPool* lightPool = pools[2];

    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    t3d_screen_clear_color(RGBA32(224, 180, 96, 0xFF));
    t3d_screen_clear_depth();

    T3DVec3 lightDirVec = { {1.0f, 1.0f, 1.0f} };
    t3d_vec3_norm(&lightDirVec);
    uint8_t colorAmbient[4] = { 0xAA, 0xAA, 0xAA, 0xFF };
    uint8_t colorDir[4] = { 0xFF, 0xAA, 0xAA, 0xFF };

    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_directional(0, colorDir, &lightDirVec);

    int lightCount = 0;

    for (int i = 0; i < lightPool->count; i++) {
        LightComponent* light = (LightComponent*)lightPool->components[i];
        if (!light->isActive) continue;

        if (light->type == LIGHT_TYPE_AMBIENT) {
            t3d_light_set_ambient(light->color);
        }
        else if (light->type == LIGHT_TYPE_DIRECTIONAL) {
            t3d_vec3_norm(&light->direction);
            t3d_light_set_directional(lightCount, light->color, &light->direction);
            lightCount++;
        }
    }
    t3d_light_set_count(lightCount);



    // Draw static map
    t3d_matrix_push(mapMatFP);
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
    t3d_model_draw(modelMap);
    t3d_matrix_pop(1);

    // Draw animated entities
    for (int i = 0; i < animPool->count; i++) {
        AnimationComponent* anim = (AnimationComponent*)animPool->components[i];
        TransformComponent* transform = (TransformComponent*)transformPool->components[i];

        // Use transform matrix
        t3d_matrix_push(&transform->matrix);
        rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        t3d_model_draw_skinned(model, anim->skeleton);
        t3d_matrix_pop(1);

        // Shadow
        t3d_matrix_push(&transform->matrix);
        rdpq_set_prim_color(RGBA32(0, 0, 0, 120));
        t3d_model_draw(modelShadow);
        t3d_matrix_pop(1);
    }

    rdpq_detach_show();
}


/*

T3DModel* model;
T3DModel* modelMap;
T3DModel* modelShadow;

T3DMat4FP* modelMatFP;
T3DMat4FP* mapMatFP;

*/