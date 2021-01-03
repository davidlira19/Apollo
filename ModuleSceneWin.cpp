#include "Globals.h"
#include "Application.h"
#include "ModuleSceneWin.h"
#include"FadeToBlack.h"


ModuleSceneWin::ModuleSceneWin(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneWin::~ModuleSceneWin()
{}

// Load assets
bool ModuleSceneWin::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	winTexture = App->textures->Load("Assets/Textures/win_screen.png");
	return ret;
}

// Load assets
bool ModuleSceneWin::CleanUp()
{
	LOG("Unloading Win scene");
	App->textures->Unload(winTexture);
	return true;
}

// Update: draw background
update_status ModuleSceneWin::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene_intro, 60);
	}
	App->renderer->Blit(winTexture, 0, 0);
	return UPDATE_CONTINUE;
}
