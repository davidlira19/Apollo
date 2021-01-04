#pragma once

#include"Timer.h"
#include "Defs.h"
#include "PerfTimer.h"
#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "BodyManager.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneLose.h"
#include "ModuleSceneWin.h"
#include "ModuleScene.h"
#include"FadeToBlack.h"
#include"Collisions.h"

class Application
{
public:
	bodyManager* bodyesManager;
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleSceneLose* scene_lose;
	ModuleSceneWin* scene_win;
	ModuleScene* scene;
	ModulePhysics* physics;
	ModuleFadeToBlack* fade;
	collision* collisions;
private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Awake();
	bool Init();
	update_status Update();
	bool CleanUp();

private:
	uint frames;
	PerfTimer ptimer;
	PerfTimer dif;

	uint frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	int lastSecFrameCount = 0;
	int prevLastSecFrameCount = 0;

	float dt = 0.0f;
	void AddModule(Module* mod);

	int cappedMs = -1;

public:
	int maxFPS;
};