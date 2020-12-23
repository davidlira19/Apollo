#pragma once
#include "Module.h"
#include "Globals.h"
#include "Vec2.h"
#include "p2List.h"

class Body
{
public:
	Body();
	~Body();
public:
	//Variables
	Vec2 position;
	double rotation;
	float mass;

public:
	//Methods
	void addForce(int force);
	void addMomentum(int momentum);
};

class Planet : public Body
{
public:
	Planet();
	~Planet();
public:
	float radius;
	Vec2 localGravity;
};

class Rocket : public Body
{
public:
	Rocket();
	~Rocket();
public:
	int life;
	Vec2 acceleration;
	Vec2 velocity;
	float force;
};

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

	//Rocket* CreateRocket(Vec2 pos, double rotation, float mass, int life, Vec2 acceleration, Vec2 velocity);
	//Planet* CreatePlanet(Vec2 pos, float mass, float radius, Vec2 localGravity);

	//p2List<Body*> bodyList;
private:

	bool debug;

};

