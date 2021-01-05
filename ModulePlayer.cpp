#include"ModulePlayer.h"
#include "ModuleScene.h"
#include "ModulePhysics.h"
#include "Application.h"
#include"Globals.h"
ModulePlayer::ModulePlayer(SDL_Texture* adTexture)
{
	ship = adTexture;
	stopAnimation.PushBack({0,0,38/2,104/2});
	stopAnimation.speed = 0.0f;
	stopAnimation.loop = false;

	fireAnimation.PushBack({ 19,0,19,74 });
	fireAnimation.PushBack({ 39,0,19,74 });
	fireAnimation.PushBack({ 58,0,19,70 });
	fireAnimation.PushBack({ 77,0,19,78});
	fireAnimation.loop = true;
	fireAnimation.speed = 0.3f;
	currentAnimation = &stopAnimation;

	fuel = 5000;
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
	Vec2 finalGravity;
	p2List_item<Body*>* auxiliar=nullptr;
	auxiliar = app->bodyesManager->bodyList.getFirst();
	float distanceX;
	float distanceY;
	float distance;
	while (auxiliar != nullptr)
	{
		if (auxiliar->data->type == bodyType::Planet)
		{
			distanceX = auxiliar->data->position.x + auxiliar->data->getXMiddle() - position.x + getXMiddle();
			distanceY = auxiliar->data->position.y + auxiliar->data->getYMiddle() - position.y + getYMiddle();
			distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
			finalGravity = app->physics->GravityForce(auxiliar->data->mass, mass, distance, Vec2(distanceX, distanceY));
			velocity.y += (finalGravity.y * -2 * dt);
			velocity.x += (finalGravity.x * -2 * dt);
		}
		auxiliar = auxiliar->next;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (fuel > 0)
		{
			fuel -= (1.0f);
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation = &fireAnimation;
			currentAnimation->Update();
			app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);
			ang = ((rotation * M_PI) / 180);
			velocity.y -= (0.2 * dt * cos(ang));
			velocity.x += (0.2 * dt * sin(ang));
			
		}
	}
	else
	{
		float ang;
		SDL_Rect rec = currentAnimation->GetCurrentFrame();
		currentAnimation = &stopAnimation;
		currentAnimation->Update();
		app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);
		/*ang = ((rotation * M_PI) / 180);
		velocity.y -= (0.2 * dt * cos(ang));
		velocity.x += (0.2 * dt * sin(ang));*/
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += 0.2 * dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		rotation -= 0.2 * dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rotation += 0.2* dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		launchTorpedo();
	}


	if (velocity.y >= 1000)
	{
		velocity.y = 999;
	}
	if (velocity.y <= -1000)
	{
		velocity.y = -999;
	}
	if (velocity.x >= 1000)
	{
		velocity.x = 999;
	}
	if (velocity.x <= -1000)
	{
		velocity.x = -999;
	}

	Vec2 pos;
	pos= app->physics->Integrator(velocity, 0.00032, app->scene->gravity);
	position.y += metersToPixels(pos.y);
	position.x += metersToPixels(pos.x);
	return true;
}
void ModulePlayer::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, position.x , position.y , &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
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
void ModulePlayer::setPos(Application* app)
{
	col1->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + 20 + getYMiddle());
	col2->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + 40 + getYMiddle());
	col3->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -40 + getYMiddle());
	col4->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -30 + getYMiddle());
	col5->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -20 + getYMiddle());
	col6->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -10 + getYMiddle());
}
