#include "Animations.h"


void AnimationSystem(ComponentPool* pool, float deltaTime) {
    for (int i = 0; i < pool->count; i++) {
        AnimationComponent* anim = (AnimationComponent*)pool->components[i];

        // Update idle and walk animations
        t3d_anim_update(&anim->idle, deltaTime);
        t3d_anim_set_speed(&anim->walk, anim->walkSpeed);
        t3d_anim_update(&anim->walk, deltaTime);

        if (anim->isAttacking && !anim->attackPlayed) {
            t3d_anim_set_playing(&anim->attack, true);
            t3d_anim_set_time(&anim->attack, 0.0f);
            anim->attackPlayed = true;
        }

        if (anim->attackPlayed) {
            t3d_anim_update(&anim->attack, deltaTime);
            if (!anim->attack.isPlaying) {
                anim->isAttacking = false;
                anim->attackPlayed = false;
            }
        }

        // Blend idle + walk into final skeleton
        t3d_skeleton_blend(anim->skeleton, anim->skeleton, anim->blendSkeleton, anim->blendFactor);
        t3d_skeleton_update(anim->skeleton);
    }
}