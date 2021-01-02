//#include "Globals.h"

#include"ModulePlayer.h"
#include "ModuleScene.h"
#include "ModulePhysics.h"
#include "Application.h"
#include"Globals.h"
ModulePlayer::ModulePlayer(SDL_Texture* adTexture)
{
	fire = adTexture;
	fireAnimation.PushBack({ 0,0,10,19 });
	fireAnimation.PushBack({ 0,29,12,21 });
	fireAnimation.PushBack({ 0,62,10,16 });
	fireAnimation.PushBack({ 0,88,10,24 });
	fireAnimation.PushBack({ 0,118,11,25 });
	fireAnimation.loop = true;
	fireAnimation.speed = 0.3f;
	currentAnimation = &fireAnimation;
	fuel = 1000;
	velocity.y = 1;
	rotation = 0;
	ammo = 10;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start(Application* app)
{	
	LOG("Loading player");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp(Application* app)
{
	LOG("Unloading player");
	return true;
}
bool ModulePlayer::PreUpdate(Application* app)
{
	
	return true;
}
// Update: draw background
bool ModulePlayer::Update(float dt, Application* app)
{	
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (fuel > 0)
		{
			fuel -= (1.0f);
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation->Update();
			app->renderer->Blit(fire,position.x + 8, position.y + 112, &rec, 2, 1.0f, rotation, 20, 52);
			ang = ((rotation * M_PI) / 180);
			velocity.y -= (20.0 * dt * cos(ang));
			velocity.x += (20.0 * dt * sin(ang));
		}
		else 
		{
			velocity.y += (app->scene->gravity * dt);
		}
	}
	else
	{
		velocity.y += (app->scene->gravity * dt);
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		rotation -= 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rotation += 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		launchTorpedo();
	}
	Vec2 pos;
	pos= app->physics->Integrator(velocity, dt, app->scene->gravity);
	position.y += metersToPixels(pos.y);
	position.x += metersToPixels(pos.x);
	return true;
}
void ModulePlayer::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, position.x ,position.y , &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
}
bool ModulePlayer::PostUpdate(Application* app)
{
	return true;
}
void ModulePlayer::launchTorpedo()
{
	if (ammo > 0)
	{
		ammo -= 1;
	}
}