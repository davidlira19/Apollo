#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include"ModuleRender.h"
#include"Animation.h"
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	fireanimation.PushBack({ 0,0,10,19 });
	fireanimation.PushBack({ 0,29,12,21 });
	fireanimation.PushBack({ 0,62,10,16 });
	fireanimation.PushBack({ 0,88,10,24 });
	fireanimation.PushBack({ 0,118,11,25 });
	fireanimation.loop = true;
	fireanimation.speed = 0.3f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	
	LOG("Loading player");
	velocity = 1.0f;
	gravity = 10.0f;
	//Player Position
	player.position.x = 0;
	player.position.y = 0;
	//Player Texture
	player.graphic = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	firetexture = App->textures->Load("Assets/Textures/fire.png");
	currentAnimation = &fireanimation;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(player.graphic);
	App->textures->Unload(firetexture);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{	
	

	if (player.position.y >= 656)
	{
		player.position.y = 656;
		velocity = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT|| App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		SDL_Rect rec = currentAnimation->GetCurrentFrame();
		currentAnimation->Update();
		App->renderer->Blit(firetexture, player.position.x+8, player.position.y+92, &rec,2);
		velocity -=(20.0 * dt);
	}
	else 
	{
	
		velocity += (gravity * dt);
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
	float cant = velocity * dt + ((1 / 2) * gravity * dt * dt);
	player.position.y += metersToPixels(cant);
	

	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = { 684 / 3,645 / 3,118 / 3,316 / 3 };
	App->renderer->Blit(player.graphic, player.position.x, player.position.y, &rect);
	return UPDATE_CONTINUE;
}



