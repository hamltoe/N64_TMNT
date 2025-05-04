#include "ecs/Systems/ControllerS.h"

void controller_component_spawn(ComponentPool* inputPool, InputSourceType type, EntityID id) {
    ControllerInput input;
    input.source = type;
    input.state = (ControllerState){0}; // zero state
    component_pool_add(inputPool, &input);
}


void InputSystem(ComponentPool* pool, float deltaTime) {
    for (int i = 0; i < pool->count; i++) {
        ControllerInput* input = (ControllerInput*)pool->components[i];

        if (input->source == INPUT_SOURCE_PLAYER) {
            controller_input_read(input, JOYPAD_PORT_1);
        }
        else if (input->source == INPUT_SOURCE_AI) {
            // AI logic placeholder — set input->state as needed
            controller_input_set_ai(input, 0.0f, 0.0f, false);
        }
    }

    /*
    SceneComponent* scene = (SceneComponent*)scenePool.components[0];
    if (input->state.button_start && !scene->isTransitioning) {
        scene->nextScene = SCENE_GAME;
        scene->isTransitioning = true;
    }
    */

}
