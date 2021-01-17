
#include"ModulePlayer.h"
#include "ModuleScene.h"
#include "ModulePhysics.h"
#include "Application.h"
#include"Globals.h"
#include "Fonts.h"
ModulePlayer::ModulePlayer(SDL_Texture* adTexture)
{
	ship = adTexture;
	stopAnimation.PushBack({ 0,0,38 / 2,104 / 2 });
	stopAnimation.speed = 0.0f;
	stopAnimation.loop = false;
	state = playerState::Free;
	fireAnimation.PushBack({ 19,0,19,74 });
	fireAnimation.PushBack({ 39,0,19,74 });
	fireAnimation.PushBack({ 58,0,19,70 });
	fireAnimation.PushBack({ 77,0,19,78 });
	fireAnimation.loop = true;
	fireAnimation.speed = 0.3f;
	currentAnimation = &stopAnimation;
	angularVelocity = 0.0f;
	fuel = 5000;
	velocity.y = 0;
	rotation = 0;
	ammo = 30;

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
	acceleration = Vec2(0, 0);
	Body::PreUpdate(app);
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
				Vec2 sum;
				distanceX = auxiliar->data->position.x + auxiliar->data->getXMiddle() - position.x + getXMiddle();
				distanceY = auxiliar->data->position.y + auxiliar->data->getYMiddle() - position.y + getYMiddle();
				distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
				sum = app->physics->GravityForce(auxiliar->data->mass, mass, distance, Vec2(distanceX, distanceY));
				finalForce.x -= (sum.x) * 25000;
				finalForce.y -= (sum.y) * 25000;
			}
			auxiliar = auxiliar->next;
		}
	}
	if (position.y >= 850)
	{
		Vec2 force;
		force += app->physics->AeroDragForce(1.29f, Vec2(velocity.x, velocity.y), 30.0f, 0.000021);
		finalForce.y += (force.y) * 10000;
		finalForce.x += (force.x) * 100;
	}

	if (position.y > -2000 && position.y < 0)
	{
		Vec2 buoyForce = (app->physics->BuoyancyForce(1, 9.81));
		finalForce.y += (buoyForce.y) * 0.002;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (fuel > 0)
		{
			state = playerState::Free;
			fuel -= (1.5f);
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation = &fireAnimation;
			currentAnimation->Update();
			app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);
			ang = ((rotation * M_PI) / 180);
			finalForce.y -= (20 * cos(ang));//0.2
			finalForce.x += (20 * sin(ang));
		}
		else
		{
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation = &stopAnimation;
			currentAnimation->Update();
			app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);
		}
	}
	else
	{
		float ang;
		SDL_Rect rec = currentAnimation->GetCurrentFrame();
		currentAnimation = &stopAnimation;
		currentAnimation->Update();
		app->renderer->Blit(ship, position.x, position.y, &rec, 2, 1.0f, rotation, 20, 52);

	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		//position.y += 0.1 * dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (state != playerState::Static)
		{
			if (fuel > 0)
			{
				angularVelocity += -1.5 * 0.2;
			}
		}


		//rotation -= 0.15 * dt;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (state != playerState::Static)
		{
			if (fuel > 0)
			{
				angularVelocity += 1.5 * 0.2;
			}
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		launchTorpedo(app);
	}
	if (angularVelocity < -10) {
		angularVelocity = -10;
	}
	else if (angularVelocity > 10) {
		angularVelocity = 10;
	}
	rotation += angularVelocity * 0.20;

	/*if (velocity.y >= 5)
	{
		velocity.y = 5;
	}
	if (velocity.y <= -5)
	{
		velocity.y = -5;
	}
	if (velocity.x >= 5)
	{
		velocity.x = 5;
	}
	if (velocity.x <= -5)
	{
		velocity.x = -5;
	}*/
	acceleration.x += (finalForce.x) / (mass);
	acceleration.y += (finalForce.y) / (mass);
	if (acceleration.y > 2)
	{
		acceleration.y = 2;
	}
	else if (acceleration.y < -2)
	{
		acceleration.y = -2;
	}
	if (acceleration.x > 2)
	{
		acceleration.x = 2;
	}
	else if (acceleration.x < -2)
	{
		acceleration.x = -2;
	}
	/*
	if (finalForce.y > 2)
	{
		finalForce.y = 2;
	}
	else if (finalForce.y < -2)
	{
		finalForce.y = -2;
	}
	if (finalForce.x > 2)
	{
		finalForce.x = 2;
	}
	else if (finalForce.x < -2)
	{
		finalForce.x = -2;
	}*/
	Vec2 pos;
	pos = app->physics->Integrator(&velocity, 0.064, acceleration);
	position.y += metersToPixels(pos.y);
	position.x += metersToPixels(pos.x);
	finalForce.x = 0;
	finalForce.y = 0;
	return true;
}
void ModulePlayer::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	sprintf_s(text, 10, "%2d", ammo);
	app->fonts->BlitText(app, (app->renderer->camera.x - 900) * -1, (app->renderer->camera.y - 675) * -1, app->scene->font, text);

}
bool ModulePlayer::PostUpdate(Application* app)
{
	return true;
}
void ModulePlayer::launchTorpedo(Application* app)
{
	if (ammo > 0)
	{
		float ang;
		ang = ((rotation * M_PI) / 180);
		//velocity.y = ( cos(ang));
		//velocity.x = ( sin(ang));

		app->bodyesManager->CreateTorpedo(Vec2(position.x, position.y), Vec2((sin(ang)) * 1000, (cos(ang)) * -1000), rotation, Vec2(acceleration.x, acceleration.y));
		ammo -= 1;
		app->audio->PlayFx(app->scene->shootFx);
	}
}
void ModulePlayer::setPos(Application* app)
{
	for (int i = 0; i < 6; i++)
	{
		float ang = ((-rotation * M_PI) / 180);
		ang = ang / 2;
		float cuat1[4] = { cos(ang),0,0,sin(ang) };
		int desp = 0;
		switch (i)
		{
		case 0:
			desp = 40;
			break;
		case 1:
			desp = 20;
			break;
		case 2:
			desp = -40;
			break;
		case 3:
			desp = -30;
			break;
		case 4:
			desp = -20;
			break;
		case 5:
			desp = -10;
			break;
		}
		float point[4] = { 0,0,desp,0 };
		float* semiRes = app->physics->quatMult(point, cuat1);
		float aux[4];
		aux[0] = semiRes[0];
		aux[1] = semiRes[1];
		aux[2] = semiRes[2];
		aux[3] = semiRes[3];
		float cuatNegado[4] = { cos(ang) ,0,0,-cuat1[3] };
		float* res = app->physics->quatMult(cuatNegado, aux);

		int b = res[1];
		int c = res[2];
		playerArr[i]->setPos(position.x + b + app->renderer->camera.x + getXMiddle(), position.y + c + app->renderer->camera.y + getYMiddle());

	}
}
void ModulePlayer::Collision(collider* bodies, collider* external, Application* app)
{
	if (app->bodyesManager->playerLose == false)
	{
		if ((bodies == col1 || bodies == col3 || bodies == col4 || bodies == col5 || bodies == col6))
		{
			app->bodyesManager->playerLose = true;
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
						velocity.y = velocity.y - (velocity.y * 0.3);
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
				acceleration.x = 0;
				acceleration.y = 0;
				velocity.x = 0;
				velocity.y = 0;
				state = playerState::Static;
			}
			else
			{
				app->bodyesManager->playerLose = true;

			}

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
