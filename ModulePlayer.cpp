#include"ModulePlayer.h"
#include "ModuleScene.h"
#include "ModulePhysics.h"
#include "Application.h"
#include"Globals.h"
#include "Fonts.h"
ModulePlayer::ModulePlayer(SDL_Texture* adTexture)
{
	ship = adTexture;
	stopAnimation.PushBack({0,0,38/2,104/2});
	stopAnimation.speed = 0.0f;
	stopAnimation.loop = false;
	state = playerState::Free;
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
{
	col1->toDelete = true;
	base->toDelete = true;
	col3->toDelete = true;
	col4->toDelete = true;
	col5->toDelete = true;
	col6->toDelete = true;

}

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
	if (state == playerState::Free) {
		Vec2 finalGravity;
		p2List_item<Body*>* auxiliar = nullptr;
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
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (fuel > 0)
		{
			state = playerState::Free;
			fuel -= (1.0f);
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation = &fireAnimation;
			currentAnimation->Update();
			app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);
			ang = ((rotation * M_PI) / 180);
			velocity.y -= (2 * dt * cos(ang));//0.2
			velocity.x += (2* dt * sin(ang));
			
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
		launchTorpedo(app);
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
	sprintf_s(text, 10, "%2d", ammo);
	app->fonts->BlitText(app, (app->renderer->camera.x-900) * -1, (app->renderer->camera.y - 675) * -1, app->scene->font, text);
}
bool ModulePlayer::PostUpdate(Application* app)
{
	return true;
}
void ModulePlayer::launchTorpedo(Application* app)
{
	if (ammo > 0)
	{
		app->bodyesManager->CreateTorpedo(Vec2(position.x, position.y), Vec2(velocity.x, velocity.y), rotation,Vec2(acceleration.x,acceleration.y));
		ammo -= 1;
	}
}
void ModulePlayer::setPos(Application* app)
{
	col1->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + 20 + getYMiddle());
	base->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + 40 + getYMiddle());
	col3->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -40 + getYMiddle());
	col4->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -30 + getYMiddle());
	col5->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -20 + getYMiddle());
	col6->setPos(position.x + app->renderer->camera.x + getXMiddle(), position.y + app->renderer->camera.y + -10 + getYMiddle());
}
void ModulePlayer::Collision(collider* bodies, collider* external, Application* app)
{
	if ((bodies == col1 || bodies == col3 || bodies == col4 || bodies == col5 || bodies == col6))
	{
		pendingToDelete = true;
	}
	else if (bodies == base)
	{
		if (velocity.y >= 150.0f && velocity.y < 700.0f)
		{
			velocity = app->physics->AddMomentum(velocity.x, velocity.y, velocity, 10);
			if (base->position.x < external->position.x)
			{
				if (velocity.x > 0)
				{
					velocity.x = velocity.x - (velocity.x * 0.3);
					velocity.x = -velocity.x;
				}
				else {
					velocity.x = velocity.x - (velocity.x * 0.3);
				}
			}
			else
			{
				if (velocity.x < 0)
				{
					velocity.x = velocity.x - (velocity.x * 0.3);
					velocity.x = -velocity.x;
				}
				else {
					velocity.x = velocity.x - (velocity.x * 0.3);
				}
			}

			if (base->position.y < external->position.y)
			{
				if (velocity.y > 0)
				{
					velocity.y = velocity.y-(velocity.y * 0.3);
					velocity.y = -velocity.y;
				}
				else {
					velocity.y = velocity.y - (velocity.y * 0.3);
				}
			}
			else
			{
				if (velocity.y < 0)
				{
					velocity.y = velocity.y - (velocity.y * 0.3);
					velocity.y = -velocity.y;
				}
				else {
					velocity.y = velocity.y - (velocity.y * 0.3);
				}
			}
			Vec2 pos;
			pos.x = velocity.x * 0.0016;
			pos.y = velocity.y * 0.0016;
			position.y += metersToPixels(pos.y);
			position.x += metersToPixels(pos.x);
		}
		else if (velocity.y < 150.0f)
		{
			velocity.x = 0;
			velocity.y = 0;
			state = playerState::Static;
		}
		else
		{
			pendingToDelete = true;
		}

	}
}


bool ModulePlayer::checkColliders(collider* body)
{
	if (body == col1 || body == base || body == col3 || body == col4 || body == col5 || body == col6) {
		return true;
	}
	else {
		return false;
	}
}
