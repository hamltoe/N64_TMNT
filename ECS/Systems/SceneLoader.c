#include "SceneLoader.h"
#include "World.h"
#include "t3d/t3d.h"

// Extern linker-defined boundaries
extern const SceneModule __start_scene_modules[];
extern const SceneModule __stop_scene_modules[];

void scene_registry_init(void) {
    // Could log or verify count if needed:
    int count = __stop_scene_modules - __start_scene_modules;
    debugf("SceneRegistry: %d scenes registered.\n", count);
}

void load_scene(SceneType type) {
    const SceneModule* mod = __start_scene_modules;
    while (mod < __stop_scene_modules) {
        if (mod->type == type) {
            mod->load_func();
            return;
        }
        mod++;
    }

    debugf("SceneLoader: Scene %d not found!\n", type);
}

void unload_scene(SceneType scene) {
    inputPool.count     = 0;
    animPool.count      = 0;
    transformPool.count = 0;
    cameraPool.count    = 0;
    // Extend if needed
}
