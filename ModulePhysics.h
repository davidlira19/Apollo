#pragma once
#include "Module.h"
#include "Globals.h"
#include "Vec2.h"
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	float Integrator(int velocity, float dt, float gravity);

	Vec2 GravityForce(float gravity, float M, float m, float distance, Vec2 direction);
private:

	bool debug;

};

class Body 
{
public:
	//Variables
	float x;
	float y;
	float w;
	float h;

	double rotation;

	float mass;

public:
	//Methods
	void addForce(int force);
	void addMomentum(int momentum);
};