#pragma once
#include "Module.h"
#include"ModuleSceneIntro.h"
#include"Asteroid.h"
#include "Planet.h"
#include "Ammo.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include"Collisions.h"
#include"ModulePlayer.h"
#include"ModuleTextures.h"
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
	//FX
	int shootFx;
	int destroyFx;
	int ammoFx;
	int winFx;
	int loseFx;
	int arcadeModeFx;
	int physicsModeFx;
	int moonLandingFx;
	//Fonts
	char textAsteroids[5] = { "\0" };
	int font;
	int fontAsteroids;
	int contCaution;
	char textPoints[5] = { "\0" };
	char textMaxPoints[5] = { "\0" };

	bool canWin;
	bool absorbed;
	bool canSeeColliders;
	float gravity;
	int asteroids;

	uint points;
	uint maxPoints;

	Asteroid* asteroid;
	Asteroid* asteroid2;
	Asteroid* asteroid3;
	Asteroid* asteroid4;
	Asteroid* asteroid5;
	Asteroid* asteroid6;
	Asteroid* asteroid7;
	Asteroid* asteroid8;
	Asteroid* asteroid9;
	Asteroid* asteroid10;
	Asteroid* asteroid11;
	Asteroid* asteroid12;
	Asteroid* asteroid13;
	Asteroid* asteroid14;
	Asteroid* asteroid15;
	SDL_Texture* caution;
	SDL_Texture* nebulosa;
	SDL_Texture* highScore;
	SDL_Texture* score;
	ModulePlayer* player;
	Planet* earth;
	Planet* moon;
	Ammo* maxAmmo;
	SDL_Texture* fuelBar;
	SDL_Texture* ammo;
	SDL_Texture* asteroidTexture;

	SDL_Texture* graphics;
	PhysBody* background;
	SDL_Texture* introText;
	Bouncer bouncer1;
	Bouncer bouncer2;

	Bouncer side_bouncer1;
	Bouncer side_bouncer2;

	SDL_Texture* backgroundTexture;
	SDL_Texture* backgroundTexture2;
	SDL_Texture* backgroundTexture3;

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
