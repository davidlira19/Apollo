#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"FadeToBlack.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	introText=App->textures->Load("Assets/Textures/intro.png");
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(introText);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene, 60);
	}
	App->renderer->Blit(introText, 0, 0);
	return UPDATE_CONTINUE;
}
