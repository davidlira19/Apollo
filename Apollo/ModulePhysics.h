#pragma once
#include "Module.h"
#include "Globals.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

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