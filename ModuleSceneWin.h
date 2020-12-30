#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleSceneWin;

class ModuleSceneWin : public Module
{
public:
	ModuleSceneWin(Application* app, bool start_enabled = true);
	~ModuleSceneWin();

	bool Start();
	update_status Update(float dt)override;
	bool CleanUp();

public:

	SDL_Texture* winTexture;

};
