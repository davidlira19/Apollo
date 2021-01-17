#pragma once
#include "Module.h"
#include "Globals.h"
#include "Vec2.h"
#include "p2List.h"
#include "Body.h"
#include "Asteroid.h"
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
	int axis[3];
	Vec2 Integrator(Vec2 velocity, float dt, float gravity);

	Vec2 AddMomentum(float x, float y, Vec2 velocity, float m);
	Vec2 GravityForce(double M, double m, double distance, Vec2 direction);
	Vec2 AeroLiftForce(float density, float velocity, float surface, float LiftCoeficient);
	Vec2 AeroDragForce(float density, Vec2 velocity, float surface, float DragCoeficient);
	Vec2 HydroLiftForce(float density, float velocity, float surface, float LiftCoeficient); // only if you go faaaaast!
	Vec2 HydroDragForce(float velocity, float b); // b is a constant that depends on the properties of the fluid and the dimensions of the object
	Vec2 BuoyancyForce(float density, float gravity);
	Vec2 SpringsForce(float cK, float dDisplacement);
	float* quatMult(float quat1[4], float quat2[4]);
	float vecMult(float vec1[3], float vec2[3]);
	float* cross(float vec1[3], float vec2[3]);
private:

	bool debug;

};