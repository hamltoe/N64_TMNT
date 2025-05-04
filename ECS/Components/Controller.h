//This is a player controller component. It handles user or AI input in order to control a possessed character.
#pragma once

#include <libdragon.h>
#include <stdbool.h>

typedef enum {
    INPUT_SOURCE_PLAYER,
    INPUT_SOURCE_AI
} InputSourceType;

typedef struct {
    float stick_x;
    float stick_y;
    bool button_a;
    bool button_b;
    bool button_start;
    bool button_z;
    bool button_l;
    bool button_r;
    bool button_c_up;
    bool button_c_down;
    bool button_c_left;
    bool button_c_right;
} ControllerState;

typedef struct {
    InputSourceType source;
    ControllerState state;
} ControllerInput;

/**
 * Reads input from the actual N64 controller and populates a ControllerInput.
 */
static inline void controller_input_read(ControllerInput* input, int port) {
    joypad_inputs_t joy = joypad_get_inputs(port);
    joypad_buttons_t btn = joy.buttons;

    input->source = INPUT_SOURCE_PLAYER;
    input->state.stick_x = (float)joy.stick_x / 80.0f; // normalized range -1 to 1
    input->state.stick_y = (float)joy.stick_y / 80.0f;

    input->state.button_a       = btn.a;
    input->state.button_b       = btn.b;
    input->state.button_start   = btn.start;
    input->state.button_z       = btn.z;
    input->state.button_l       = btn.l;
    input->state.button_r       = btn.r;
    input->state.button_c_up    = btn.c_up;
    input->state.button_c_down  = btn.c_down;
    input->state.button_c_left  = btn.c_left;
    input->state.button_c_right = btn.c_right;
}

/**
 * Populates an AI-controlled ControllerInput.
 * This is just an example; customize based on AI logic.
 */
static inline void controller_input_set_ai(ControllerInput* input, float x, float y, bool attack) {
    input->source = INPUT_SOURCE_AI;
    input->state.stick_x = x;
    input->state.stick_y = y;
    input->state.button_a = attack;
    input->state.button_b = false;
    input->state.button_start = false;
    input->state.button_z = false;
    input->state.button_l = false;
    input->state.button_r = false;
    input->state.button_c_up = false;
    input->state.button_c_down = false;
    input->state.button_c_left = false;
    input->state.button_c_right = false;
}
