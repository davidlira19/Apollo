#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"
#include "Fonts.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	App->bodyesManager->Enable();
	backgroundTexture = App->textures->Load("Assets/Textures/bg.png");
	fuelBar = App->textures->Load("Assets/Textures/fuel_bar.png");
	ammo = App->textures->Load("Assets/Textures/ammo.png");
	uint number = 1;
	font = App->fonts->Load(App, "Assets/Textures/numbers.png","0123456789", number);
	LOG("Loading Intro assets");
	bool ret = true;
	gravity = 10.0f;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//asteroid = App->bodyesManager->CreateAsteroid({ 100, 100 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	player = App->bodyesManager->CreatePlayer({ 670, 1500 }, 10000);
	earth = App->bodyesManager->CreatePlanet(Vec2(300,1900),1, 379, 5.972E7, 379.0f, Vec2(0, 9.81));
	moon = App->bodyesManager->CreatePlanet(Vec2(600,-12500),2, 190, 7.349E6, 190.0f, Vec2(0, 1.62));

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
	SDL_Rect rectBar = { 0,0,200,20 };
	int widthBar = (float)player->fuel / 5000 * 200;
	rectBar = { 0,0,widthBar,20 };

	LOG("%d", player->ammo);

	App->renderer->Blit(backgroundTexture, 200, -13000);
	/*App->renderer->Blit(backgroundTexture, 920, 0);
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
	App->renderer->Blit(backgroundTexture, 2760, 1554);*/

	App->renderer->camera.x = -200;
	App->renderer->camera.y = (player->position.y * -1) + 379;

	//Camera Limits
	if (App->renderer->camera.y < -1600)
	{
		App->renderer->camera.y = -1599;
	}
	if (App->renderer->camera.y > 13000)
	{
		App->renderer->camera.y = 12999;
	}


	//if (player->position.x > 3500 || player->position.x < -30 || player->position.y > 2030 || player->position.y < -30 || player->fuel <= 0)
	//{
	//	App->fade->FadeToBlack((Module*)this, (Module*)App->scene_lose, 60);
	//}


	p2List_item<collider*>* auxiliar;
	auxiliar = App->collisions->colliderList.getFirst();
	while (auxiliar != nullptr)
	{
		App->renderer->DrawCircle(auxiliar->data->position.x,auxiliar->data->position.y, auxiliar->data->circleRad, 255, 0, 0, 255);
		auxiliar = auxiliar->next;
	}

	App->renderer->Blit(fuelBar, App->renderer->camera.x * -1, App->renderer->camera.y * -1, &rectBar);
	App->renderer->Blit(ammo, App->renderer->camera.x * -1 +800, App->renderer->camera.y * -1+650);
	
	return UPDATE_CONTINUE;
}
