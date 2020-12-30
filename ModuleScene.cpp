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
	LOG("Loading Intro assets");
	bool ret = true;
	gravity = 10.0f;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//earth = App->body->CreatePlanet(Vec2(0, 0),20, 0, 100, Vec2(0, 0));
	//rocket = App->bodyesManager->CreateRocket({ 100, 100 },20, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	player = App->bodyesManager->CreatePlayer({ 100, 100 }, 100);
	

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
	/*if (rocket->position.y >= 656)
	{
		rocket->position.y = 656;
		rocket->velocity.y = 0;
		rocket->velocity.x = 0;
	}*/

	

	/*if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->player, 60);
	}*/
	//App->renderer->Blit(introText, 0, 0);

	SDL_Rect rocket_rect = { 186,215,42,124 };
	/*App->renderer->Blit(rocket->rocketTexture, rocket->position.x, rocket->position.y, &rocket_rect, 1, 1.0f, rocket->rotation);
	App->renderer->DrawCircle(earth->position.x, earth->position.y, earth->radius, 255, 0, 0, 255);*/




	p2List_item<collider*>* auxiliar;
	auxiliar = App->collisions->colliderList.getFirst();
	while (auxiliar != nullptr)
	{

		App->renderer->DrawCircle(auxiliar->data->position.x, auxiliar->data->position.y, auxiliar->data->circleRad, 255, 0, 0, 255);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
