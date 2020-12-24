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

Vec2 ModulePhysics::GravityForce(double gravity, double M, double m, double distance, Vec2 direction)
{
	double G = pow(6.674,-11);
	Vec2 Fg = Vec2(0, 0);
	double F_x = -G * (m * M / (distance * distance)) * direction.x;
	double F_y = -G * (m * M / (distance * distance)) * direction.y;

	Fg = Vec2((float)F_x, (float)F_y);

	return Fg;
}

Vec2 ModulePhysics::LiftForce(float density, float velocity, float surface, float LiftCoeficient)
{
	Vec2 Flift = { 0, (density * velocity * velocity * surface * LiftCoeficient) / 2 };
	return Flift;
}

Vec2 ModulePhysics::DragForce(float density, float velocity, float surface, float DragCoeficient)
{
	Vec2 Fdrag = { (density * velocity * velocity * surface * DragCoeficient) / 2,0 };
	return Fdrag;
}

Vec2 ModulePhysics::AddMomentum(float x, float y, Vec2 velocity, float m)
{
	float Xvelocity = x / m;
	float Yvelocity = y / m;
	velocity.x += Xvelocity;
	velocity.y += Yvelocity;
	
	return velocity;
}

Rocket* ModulePhysics::CreateRocket(Vec2 pos, double rotation, float mass, int life, int ammo, float fuel, Vec2 acceleration, Vec2 velocity)
{
	Rocket* rocket = new Rocket();
	rocket->position = pos;
	rocket->rotation = rotation;
	rocket->mass = mass;
	rocket->life = life;
	rocket->ammo = ammo;
	rocket->fuel = fuel;
	rocket->acceleration = acceleration;
	rocket->velocity = velocity;

	bodyList.add(rocket);

	return rocket;
}

Planet* ModulePhysics::CreatePlanet(Vec2 pos, float mass, float radius, Vec2 localGravity)
{
	Planet* planet = new Planet();
	planet->position = pos;
	planet->mass = mass;
	planet->radius = radius;
	planet->localGravity = localGravity;

	bodyList.add(planet);
	return planet;
}

