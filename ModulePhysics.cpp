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
	Vec2 Fg = GravityForce(9.81, 100000000, 20000000, 200, { 100,200 });
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
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

Vec2 ModulePhysics::GravityForce(float gravity, float M, float m, float distance, Vec2 direction)
{
	float G = pow(6.674,-11);
	Vec2 Fg = { -G * (m * M / (distance * distance)) * direction.x,-G * (m * M / (distance * distance)) * direction.y };

	return Fg;
}
