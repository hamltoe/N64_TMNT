#pragma once

#include "Scene.h"
#include "World.h"

void load_scene_menu(World* world);
void load_scene_game(World* world, EntityID player);
void scene_load_demo(World* world);

void SceneSystem(World* world, float deltaTime);

void scene_on_enter(SceneType scene);
void scene_on_exit(SceneType scene);
