//The controller is used to handle player and AI input in order to controll a character or possessed obect.

#include <libdragon.h>

void controller_component_spawn(ComponentPool* inputPool, InputSourceType type, EntityID id);

void InputSystem(ComponentPool* pool, float deltaTime);
