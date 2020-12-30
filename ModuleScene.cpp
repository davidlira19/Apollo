#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"



ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	fireAnimation.PushBack({ 0,0,10,19 });
	fireAnimation.PushBack({ 0,29,12,21 });
	fireAnimation.PushBack({ 0,62,10,16 });
	fireAnimation.PushBack({ 0,88,10,24 });
	fireAnimation.PushBack({ 0,118,11,25 });
	fireAnimation.loop = true;
	fireAnimation.speed = 0.3f;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	gravity = 10.0f;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	earth = App->physics->CreatePlanet(Vec2(0, 0), 0, 100, Vec2(0, 0));
	rocket = App->physics->CreateRocket(Vec2(100, 100), 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	rocket->rocketTexture = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	fireTexture = App->textures->Load("Assets/Textures/fire.png");
	App->collisions->addCollider(35, colliderType::roket, this, 0, 0);

	playerColl = App->collisions->addCollider(10, colliderType::player, this, 70, 70);
	currentAnimation = &fireAnimation;

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	
	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	playerColl->setPos(rocket->position.x, rocket->position.y);
	if (rocket->position.y >= 656)
	{
		rocket->position.y = 656;
		rocket->velocity.y = 0;
		rocket->velocity.x = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (rocket->fuel > 0)
		{
			rocket->fuel -= (1.0f);
			float ang;
			SDL_Rect rec = currentAnimation->GetCurrentFrame();
			currentAnimation->Update();
			App->renderer->Blit(fireTexture, rocket->position.x + 8, rocket->position.y + 112, &rec, 2, 1.0f, rocket->rotation, 20, 52);
			ang = ((rocket->rotation * M_PI) / 180);
			rocket->velocity.y -= (20.0 * dt * cos(ang));
			rocket->velocity.x += (20.0 * dt * sin(ang));
		}
	}
	else
	{
		rocket->velocity.y += (gravity * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		rocket->position.y += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		rocket->rotation -= 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rocket->rotation += 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		rocket->launchTorpedo();
	}

	Vec2 ps;
	ps = App->physics->Integrator(rocket->velocity, dt, gravity);

	rocket->position.y += metersToPixels(ps.y);
	rocket->position.x += metersToPixels(ps.x);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->player, 60);
	}
	App->renderer->Blit(introText, 0, 0);

	SDL_Rect rocket_rect = { 186,215,42,124 };
	App->renderer->Blit(rocket->rocketTexture, rocket->position.x, rocket->position.y, &rocket_rect, 1, 1.0f, rocket->rotation);
	App->renderer->DrawCircle(earth->position.x, earth->position.y, earth->radius, 255, 0, 0, 255);




	p2List_item<collider*>* auxiliar;
	auxiliar = App->collisions->colliderList.getFirst();
	while (auxiliar != nullptr)
	{

		App->renderer->DrawCircle(auxiliar->data->position.x, auxiliar->data->position.y, auxiliar->data->circleRad, 255, 0, 0, 255);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
