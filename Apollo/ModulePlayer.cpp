#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include"ModuleRender.h"
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	ship=App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(ship);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = { 684,645,118,316 };
	App->renderer->Blit(ship, 0, 0, &rect);
	return UPDATE_CONTINUE;
}



