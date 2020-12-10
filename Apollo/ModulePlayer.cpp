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
	velocity = 0.0f;
	gravity = 0.001f;
	//Player Position
	player.position.x = 0;
	player.position.y = 0;
	//Player Texture
	player.graphic = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(player.graphic);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{	
	velocity += gravity * 0.05f * 100.0f;
	player.position.y += velocity * 0.05f * 100.0f;

	if (player.position.y >= 656)
	{
		player.position.y = 656;
		velocity = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		velocity = 0;
		player.position.y -= 6;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		player.position.y += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		player.position.x -= 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		player.position.x += 2;
	}

	SDL_Rect rect = { 684 / 3,645 / 3,118 / 3,316 / 3 };
	App->renderer->Blit(player.graphic, player.position.x, player.position.y, &rect);

	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate()
{
	
	return UPDATE_CONTINUE;
}



