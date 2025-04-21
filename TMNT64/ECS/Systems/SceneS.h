

void load_scene_menu(ComponentPool* scenePool);

void load_scene_game(ComponentPool* scenePool, ComponentPool* animPool, ComponentPool* transformPool, EntityID entity);

void SceneSystem(ComponentPool** pools, float deltaTime);

void scene_on_enter(SceneType scene);

void scene_on_exit(SceneType scene);

