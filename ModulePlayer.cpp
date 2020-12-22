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
	velocity.y = 0.0f;
	velocity.x = 0.0f;
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
		velocity.y = 0;
		velocity.x = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		float ang;
		SDL_Rect rec = currentAnimation->GetCurrentFrame();
		currentAnimation->Update();
		App->renderer->Blit(firetexture, player.position.x + 8, player.position.y + 92, &rec, 2, 1.0f, angle, 20, 52);
		ang = ((angle * M_PI) / 180);
		velocity.y -= (20.0 * dt * cos(ang));
		velocity.x += (20.0 * dt * sin(ang));

	}
	else
	{

		velocity.y += (gravity * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		player.position.y += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		angle -= 1;

	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		angle += 1;

	}

	
	Vec2 ps;
	ps = App->physics->Integrator(velocity, dt, gravity);

	App->player->player.position.y += metersToPixels(ps.y);
	App->player->player.position.x += metersToPixels(ps.x);
	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = { 684 / 3,645 / 3,118 / 3,316 / 3 };
	App->renderer->Blit(player.graphic, player.position.x, player.position.y, &rect, 1, 1.0f, angle, 20, 52);
	return UPDATE_CONTINUE;
}



