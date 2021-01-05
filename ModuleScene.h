#pragma once
#include "Module.h"
#include"ModuleSceneIntro.h"
#include"Asteroid.h"
#include "Planet.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include"Collisions.h"
#include"ModulePlayer.h"
#define BOUNCER_TIME 200

class ModuleScene;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt)override;
	bool CleanUp();

public:
	float gravity;
	Asteroid* asteroid;
	ModulePlayer* player;
	Planet* earth;
	Planet* moon;
	SDL_Texture* fuelBar;
	SDL_Texture* ammo;

	SDL_Texture* graphics;
	PhysBody* background;
	SDL_Texture* introText;
	Bouncer bouncer1;
	Bouncer bouncer2;

	Bouncer side_bouncer1;
	Bouncer side_bouncer2;
	SDL_Texture* backgroundTexture;
	SDL_Texture* tex_light_tiny;
	SDL_Texture* tex_light_medium;
	SDL_Texture* tex_light_big;

	uint fx_light_tiny;
	uint fx_light_medium;
	uint fx_light_big;

	p2DynArray<Light> lights;
	
	PhysBody* player_lose;
	uint player_lose_fx;
};
