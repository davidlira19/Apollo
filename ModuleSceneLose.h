#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleSceneLose;

class ModuleSceneLose : public Module
{
public:
	ModuleSceneLose(Application* app, bool start_enabled = true);
	~ModuleSceneLose();

	bool Start();
	update_status Update(float dt)override;
	bool CleanUp();

public:

	SDL_Texture* loseTexture;

};
