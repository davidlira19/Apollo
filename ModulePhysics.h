#pragma once
#include "Module.h"
#include "Globals.h"
#include "Vec2.h"
#include "p2List.h"
#include "Body.h"
#include "Rocket.h"
#include "Planet.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	Vec2 Integrator(Vec2 velocity, float dt, float gravity);

	Vec2 GravityForce(float gravity, float M, float m, float distance, Vec2 direction);
	Vec2 LiftForce(float density, float velocity, float surface, float LiftCoeficient);
	Vec2 DragForce(float density, float velocity, float surface, float DragCoeficient);
	Vec2 AddMomentum(float x, float y, Vec2 velocity, float m);

	Rocket* CreateRocket(Vec2 pos, double rotation, float mass, int life,int ammo, Vec2 acceleration, Vec2 velocity);
	Planet* CreatePlanet(Vec2 pos, float mass, float radius, Vec2 localGravity);

	p2List<Body*> bodyList;
private:

	bool debug;

};