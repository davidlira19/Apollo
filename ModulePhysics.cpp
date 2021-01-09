#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"

#include "math.h"


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	//Vec2 Fg = GravityForce(9.81, 100000000, 20000000, 200, { 100,200 });
	//float moduleFg = sqrt((Fg.x * Fg.x) + (Fg.y * Fg.y));
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate(Application* app)
{

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	return true;
}

Vec2 ModulePhysics::Integrator(Vec2 velocity, float dt, float gravity) {
	Vec2 pos;
	pos.y = velocity.y * dt + ((1 / 2) * gravity * dt * dt);
	pos.x = velocity.x * dt;
	return pos;
}

Vec2 ModulePhysics::GravityForce(double M, double m, double distance, Vec2 direction)
{
	const double G = 6.674E-11;
	Vec2 Fg = Vec2(0, 0);
	double F_x = -G * (m * M / (distance * distance)) * direction.x;
	double F_y = -G * (m * M / (distance * distance)) * direction.y;

	Fg = Vec2((float)F_x, (float)F_y);

	return Fg;
}

Vec2 ModulePhysics::AeroLiftForce(float density, float velocity, float surface, float LiftCoeficient)
{
	return Vec2(0, (density * velocity * velocity * surface * LiftCoeficient) / 2);
}

Vec2 ModulePhysics::AeroDragForce(float density, float velocity, float surface, float DragCoeficient)
{
	return Vec2((density * velocity * velocity * surface * DragCoeficient) / 2, 0);
}

Vec2 ModulePhysics::HydroLiftForce(float density, float velocity, float surface, float LiftCoeficient)
{
	return Vec2( 0, (density * velocity * velocity * surface * LiftCoeficient) / 2 );
}

Vec2 ModulePhysics::HydroDragForce(float velocity, float b)
{
	return Vec2(-b * velocity, 0);
}

Vec2 ModulePhysics::BuoyancyForce(float density, float gravity, float volume, float mass)
{
	return Vec2(0, (density * gravity * volume) - (mass * gravity));
}

Vec2 ModulePhysics::SpringsForce(float cK, float dDisplacement)
{
	return Vec2(-cK * dDisplacement, 0);
}

Vec2 ModulePhysics::AddMomentum(float x, float y, Vec2 velocity, float m)
{
	float Xvelocity = x / m;
	float Yvelocity = y / m;
	velocity.x += Xvelocity;
	velocity.y += Yvelocity;
	
	return velocity;
}


