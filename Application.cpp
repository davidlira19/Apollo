#include "Application.h"

Application::Application()
{
	frames = 0;
	PERF_START(ptimer);

	bodyesManager = new bodyManager(this, false);
	renderer = new ModuleRender(this,true);
	window = new ModuleWindow(this, true);
	textures = new ModuleTextures(this, true);
	input = new ModuleInput(this, true);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this, true);
	scene_lose = new ModuleSceneLose(this, false);
	scene_win = new ModuleSceneWin(this, false);
	scene = new ModuleScene(this, false);
	fonts = new Fonts(this, false);
	physics = new ModulePhysics(this, true);
	fade = new ModuleFadeToBlack(this, true);
	collisions = new collision(this, true);
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	
	AddModule(textures);
	AddModule(input);
	AddModule(audio);
	AddModule(fade);
	AddModule(fonts);
	// Scenes
	AddModule(scene_intro);
	AddModule(scene_lose);
	AddModule(scene_win);
	AddModule(scene);
	// Player
	AddModule(bodyesManager);
	AddModule(collisions);
	AddModule(renderer);

	PERF_PEEK(ptimer);
}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Awake()
{
	PERF_START(ptimer);
	maxFPS = 16;
	PERF_PEEK(ptimer);
	return true;
}

bool Application::Init()
{
	PERF_START(ptimer);
	maxFPS = 16;
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	PERF_PEEK(ptimer);
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	frameCount++;
	lastSecFrameCount++;

	dt = frameTime.Read();
	frameTime.Start();

	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();
	//dt = frameTime.ReadSec();
	//frameTime.Start();
	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate(this);
		item = item->next;
	}

	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float averageFps = float(frameCount) / startupTime.ReadSec();
	float secondsSinceStartup = startupTime.ReadSec();
	uint lastFrameMs = frameTime.Read();
	uint framesOnLastUpdate = prevLastSecFrameCount;

	static char title[256];
	sprintf_s(title, 256, "FPS: %i / Avg.FPS: %.2f / Last-Frame MS: %.3f", framesOnLastUpdate, averageFps, dt);
	window->SetTitle(title);

	if (maxFPS > 0 && lastFrameMs < maxFPS)
	{
		PERF_START(ptimer);
		SDL_Delay(maxFPS-lastFrameMs);
		PERF_PEEK(ptimer);

	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}