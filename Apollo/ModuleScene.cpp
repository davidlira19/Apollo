#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	ship = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(ship);
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	SDL_Rect rect = { 684,645,118,316 };
	App->renderer->Blit(ship, 0, 0, &rect);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->player, 60);
	}
	App->renderer->Blit(introText, 0, 0);
	return UPDATE_CONTINUE;
}
