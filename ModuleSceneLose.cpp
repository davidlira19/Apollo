#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLose.h"
#include"FadeToBlack.h"


ModuleSceneLose::ModuleSceneLose(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneLose::~ModuleSceneLose()
{}

// Load assets
bool ModuleSceneLose::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	loseTexture = App->textures->Load("Assets/Textures/lose_screen.png");
	return ret;
}

// Load assets
bool ModuleSceneLose::CleanUp()
{
	LOG("Unloading Lose scene");
	App->textures->Unload(loseTexture);
	return true;
}

// Update: draw background
update_status ModuleSceneLose::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene_win, 60);
	}
	App->renderer->Blit(loseTexture, 0, 0);
	return UPDATE_CONTINUE;
}
