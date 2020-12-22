#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody
{
};

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;
	p2Point<int> position;

	Object() : graphic(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();
	SDL_Texture* firetexture;
	bool Start();
	update_status Update(float dt)override;
	update_status PostUpdate()override;
	bool CleanUp();
	Animation fireanimation;
	Animation* currentAnimation;
public:
	float velocity;
	float gravity;
	float angle;
	Object player;
};