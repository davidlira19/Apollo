#ifndef _BODYMANAGER_H_
#define _BODYMANAGER_H_
#include"p2List.h"
#include"Body.h"
#include"Module.h"
#include"Globals.h"
#include"Asteroid.h"
#include"planet.h"
#include "Torpedo.h"
#include "Ammo.h"
#include"ModulePlayer.h"
#include"Fire.h"
class bodyManager :public Module 
{
public:
	bodyManager(Application* app, bool start_enabled = true);
	~bodyManager();
	void OnCollision(collider* body1, collider* body2, Application* app)override;
	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();
	Asteroid* CreateAsteroid(Vec2 pos, int rad, double rotation, float mass, int life, int ammo, float fuel, Vec2 acceleration, Vec2 velocity);
	Ammo* CreateAmmo(Vec2 pos);
	Planet* CreatePlanet(Vec2 pos,int type, float mass, float radius, Vec2 localGravity);
	Torpedo* CreateTorpedo(Vec2 pos, Vec2 velocity, double rotation, Vec2 acceleration);
	ModulePlayer* CreatePlayer(Vec2 pos, float mass);
	Fire* CreateFire(int x,int y);
	Fire* finalFire;
	p2List<Body*>bodyList;
	SDL_Texture* Texture;
	SDL_Texture* Texture1;
	SDL_Texture* Texture2;
	SDL_Texture* Texture3;
	SDL_Texture* TextureAmmo;
	SDL_Texture* fireText;
	int fire1;
	int fire2;
	int fire3;
	int fire4;
	int counterToFire;
	bool playerLose;
	bool count;
};
#endif



