#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"



ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	backgroundTexture = App->textures->Load("Assets/Textures/background.png");
	LOG("Loading Intro assets");
	bool ret = true;
	gravity = 10.0f;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	asteroid = App->bodyesManager->CreateAsteroid({ 100, 100 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	player = App->bodyesManager->CreatePlayer({ 100, 100 }, 100);
	earth = App->bodyesManager->CreatePlanet(Vec2(0, -500), 100, 5.972E24, 100.0f, Vec2(0, 9.81));
	moon = App->bodyesManager->CreatePlanet(Vec2(1000, 1000), 50, 7.349E22, 50.0f, Vec2(0, 1.62));

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
	LOG("%d %d", player->position.x, player->position.y);

	App->renderer->Blit(backgroundTexture, 0, 0);
	App->renderer->Blit(backgroundTexture, 920, 0);
	App->renderer->Blit(backgroundTexture, 0, 518);
	App->renderer->Blit(backgroundTexture, 1840, 0);
	App->renderer->Blit(backgroundTexture, 0, 1036);
	App->renderer->Blit(backgroundTexture, 2760, 0);
	App->renderer->Blit(backgroundTexture, 0, 1554);

	App->renderer->Blit(backgroundTexture, 920, 518);
	App->renderer->Blit(backgroundTexture, 920, 1036);
	App->renderer->Blit(backgroundTexture, 920, 1554);

	App->renderer->Blit(backgroundTexture, 1840, 518);
	App->renderer->Blit(backgroundTexture, 1840, 1036);
	App->renderer->Blit(backgroundTexture, 1840, 1554);

	App->renderer->Blit(backgroundTexture, 2760, 518);
	App->renderer->Blit(backgroundTexture, 2760, 1036);
	App->renderer->Blit(backgroundTexture, 2760, 1554);

	App->renderer->camera.x = (player->position.x * -1) - 512;
	App->renderer->camera.y = (player->position.y * -1) - 379;

	//Camera Limits
	if (App->renderer->camera.y < -1300)
	{
		App->renderer->camera.y = -1299;
	}
	if (App->renderer->camera.y > 0)
	{
		App->renderer->camera.y = -1;
	}
	if (App->renderer->camera.x > 0)
	{
		App->renderer->camera.x = -1;
	}
	if (App->renderer->camera.x < -2500)
	{
		App->renderer->camera.x = -2499;
	}

	p2List_item<collider*>* auxiliar;
	auxiliar = App->collisions->colliderList.getFirst();
	while (auxiliar != nullptr)
	{

		App->renderer->DrawCircle(auxiliar->data->position.x, auxiliar->data->position.y, auxiliar->data->circleRad, 255, 0, 0, 255);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
