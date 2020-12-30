#ifndef _BODYMANAGER_H_
#define _BODYMANAGER_H_
#include"p2List.h"
#include"Body.h"
#include"Module.h"
#include"Globals.h"
#include"Rocket.h"
#include"planet.h"
#include"ModulePlayer.h"

class bodyManager :public Module 
{
public:
	bodyManager(Application* app, bool start_enabled = true);
	~bodyManager();
	void OnCollision(collider* body1, collider* body2);
	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();
	Rocket* CreateRocket(Vec2 pos, int rad, double rotation, float mass, int life, int ammo, float fuel, Vec2 acceleration, Vec2 velocity);
	Planet* CreatePlanet(Vec2 pos, int rad, float mass, float radius, Vec2 localGravity);
	ModulePlayer* CreatePlayer(Vec2 pos, float mass);
	p2List<Body*>bodyList;
	SDL_Texture* Texture;
	SDL_Texture* fireText;
};
#endif



