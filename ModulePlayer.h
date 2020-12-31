#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Vec2.h"

class PhysBody
{
};

/*struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;
	Vec2 position;

	Object() : graphic(NULL), body(NULL)
	{}
};*/

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();
	bool Start();
	update_status Update(float dt)override;
	update_status PostUpdate()override;
	bool CleanUp();
};