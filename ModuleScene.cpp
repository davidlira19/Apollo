#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"
#include "Fonts.h"
#include"ModuleRender.h"

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
	asteroids = 15;
	asteroidTexture = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	uint number = 1;
	uint asteroidsLeft = 1;
	font = App->fonts->Load(App, "Assets/Textures/numbers.png","0123456789", number);
	fontAsteroids = App->fonts->Load(App, "Assets/Textures/numbers.png","0123456789", asteroidsLeft);
	LOG("Loading Intro assets");
	bool ret = true;
	gravity = 10.0f;
	canWin = false;
	absorbed = false;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	asteroid = App->bodyesManager->CreateAsteroid({ 300, 1000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid2 = App->bodyesManager->CreateAsteroid({ 600, 500 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid3 = App->bodyesManager->CreateAsteroid({ 700, 0 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid4 = App->bodyesManager->CreateAsteroid({ 300, -500 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid5 = App->bodyesManager->CreateAsteroid({ 350, -1000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid6 = App->bodyesManager->CreateAsteroid({ 150, -2000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid7 = App->bodyesManager->CreateAsteroid({ 700, -3000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid8 = App->bodyesManager->CreateAsteroid({ 400, -4500 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid9 = App->bodyesManager->CreateAsteroid({ 200, -6000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid10 = App->bodyesManager->CreateAsteroid({ 600, -7000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid11 = App->bodyesManager->CreateAsteroid({ 300, -8000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid12 = App->bodyesManager->CreateAsteroid({ 200, -9000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid13 = App->bodyesManager->CreateAsteroid({ 100, -10000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid14 = App->bodyesManager->CreateAsteroid({ 800, -10500 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));
	asteroid15 = App->bodyesManager->CreateAsteroid({ 400, -11000 },30, 0, 100, 100, 50, 1500, Vec2(0, 0), Vec2(0, 0));

	player = App->bodyesManager->CreatePlayer({ 670, 1700 }, 100);
	earth = App->bodyesManager->CreatePlanet(Vec2(300,1900),1, 379, 5.972E7, 379.0f, Vec2(0, 9.81));
	moon = App->bodyesManager->CreatePlanet(Vec2(600,-12500),2, 190, 14.349E6, 190.0f, Vec2(0, 1.62));
	maxAmmo = App->bodyesManager->CreateAmmo(Vec2(400, -7000));
	nebulosa = App->textures->Load("Assets/Textures/nebulosa.png");

	shootFx = App->audio->LoadFx("Assets/Audio/shoot.wav");
	destroyFx = App->audio->LoadFx("Assets/Audio/destroy.wav");
	ammoFx = App->audio->LoadFx("Assets/Audio/ammo.wav");

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	App->textures->Unload(backgroundTexture);
	App->textures->Unload(fuelBar);
	App->textures->Unload(ammo);
	App->fonts->UnLoad(App,font);
	LOG("Unloading Intro scene");	
	return true;
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	SDL_Rect rectBar = { 0,0,200,20 };
	int widthBar = (float)player->fuel / 5000 * 200;
	rectBar = { 0,0,widthBar,20 };

	LOG("%d", canWin);

	App->renderer->Blit(backgroundTexture, 200, -13000);
	App->renderer->Blit(nebulosa, 200, -5000);

	App->renderer->camera.x = -200;
	App->renderer->camera.y = ( metersToPixels(player->position.y)* -1) + 379;
	
	LOG("%f", player->position.x);

	//Camera Limits
	if (App->renderer->camera.y < -1600)
	{
		App->renderer->camera.y = -1599;
	}
	if (App->renderer->camera.y > 13000)
	{
		App->renderer->camera.y = 12999;
	}

	if (pixelsToMeters(player->position.y <= -5000))
	{
		absorbed = true;
	}
	else if (pixelsToMeters(player->position.y >= -3000))
	{
		absorbed = false;
	}

	/*p2List_item<collider*>* auxiliar;
	auxiliar = App->collisions->colliderList.getFirst();
	while (auxiliar != nullptr)
	{
		App->renderer->DrawCircle(auxiliar->data->position.x,auxiliar->data->position.y, auxiliar->data->circleRad, 255, 0, 0, 255);
		auxiliar = auxiliar->next;
	}*/

	App->renderer->Blit(fuelBar, App->renderer->camera.x * -1, App->renderer->camera.y * -1, &rectBar);
	App->renderer->Blit(ammo, App->renderer->camera.x * -1 +800, App->renderer->camera.y * -1+650);

	sprintf_s(textAsteroids, 5, "%2d", asteroids);
	App->fonts->BlitText(App, (App->renderer->camera.x - 900) * -1, (App->renderer->camera.y - 560) * -1, fontAsteroids, textAsteroids);

	SDL_Rect section = {0,132,72,73};
	App->renderer->Blit(asteroidTexture, (App->renderer->camera.x - 820) * -1, (App->renderer->camera.y - 550) * -1, &section);

	App->renderer->DrawLine(-200, 0, 5000, -10, 255, 0, 0);
	App->renderer->DrawLine(-200,-2000,5000,-2010,255,0,0);
	
	return UPDATE_CONTINUE;
}
