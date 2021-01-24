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

Vec2 ModulePhysics::Integrator(Vec2* velocity, float dt, Vec2 acceleration) 
{
	Vec2 pos;

	pos.y += velocity->y * dt + ((0.5) * acceleration.y * dt * dt);
	pos.x += velocity->x * dt + ((0.5) * acceleration.x * dt * dt);
	velocity->x += acceleration.x * dt;
	velocity->y += acceleration.y * dt;

	return pos;
}

Vec2 ModulePhysics::GravityForce(double M, double m, double distance, Vec2 direction)
{
	const double G = 0.010;
	Vec2 Fg = Vec2(0, 0);
	double F_x = -G * (m * M / (distance* distance)) * direction.x;
	double F_y = -G * (m * M / (distance* distance)) * direction.y;

	Fg = Vec2((float)F_x, (float)F_y);

	return Fg;
}

Vec2 ModulePhysics::AeroLiftForce(float density, float velocity, float surface, float LiftCoeficient)
{
	return Vec2(0, (density * velocity * velocity * surface * LiftCoeficient) / 2);
}

Vec2 ModulePhysics::AeroDragForce(float density, Vec2 velocity, float surface, float DragCoeficient)
{

	
	float modVelocity = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	Vec2 direction = velocity;
	direction.x = direction.x / modVelocity;
	direction.y = direction.y / modVelocity;
	if (modVelocity == 0) 
	{
		return Vec2(0, 0);
	}
	return Vec2(((density * modVelocity* modVelocity * surface * DragCoeficient) / 2) * direction.x, ((density * modVelocity* modVelocity * surface * DragCoeficient) / 2) * direction.y);
	
}

Vec2 ModulePhysics::HydroLiftForce(float density, float velocity, float surface, float LiftCoeficient)
{
	return Vec2( 0, (density * velocity * velocity * surface * LiftCoeficient) / 2 );
}

Vec2 ModulePhysics::HydroDragForce(ModulePlayer *player)
{
	Vec2 hydroDragForce;

	float velocityCoeficient = 15.0f;

	Vec2 bodyVelocity = player->velocity;

	float velocity = sqrt((bodyVelocity.x * bodyVelocity.x) + (bodyVelocity.y * bodyVelocity.y));

	float forceDrag = velocityCoeficient * velocity;

	Vec2 direction = player->velocity;
	float module = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	direction.x = direction.x / module;
	direction.y = direction.y / module;

	direction.x = -direction.x;
	direction.y = -direction.y;

	Vec2 dragVector;
	dragVector.x = direction.x * forceDrag;
	dragVector.y = direction.y * forceDrag;


	
	return dragVector;
}

Vec2 ModulePhysics::BuoyancyForce(float density, float gravity, float waterLevel)
{

	float area = 0;
	
	if (App->scene->player->position.y > pixelsToMeters(waterLevel))
	{
		area = pixelsToMeters(40) * pixelsToMeters(103);
		
	}
	else if (App->scene->player->position.y + pixelsToMeters(103)  < pixelsToMeters(waterLevel) )
	{
		area = 0;
	}
	else
	{
		float dif = pixelsToMeters(103) - (pixelsToMeters(waterLevel) - App->scene->player->position.y);
		area = pixelsToMeters(40) * dif;
	}
	
	return Vec2(0, (density * gravity * area));
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
float* ModulePhysics::quatMult(float quat1[4], float quat2[4])
{
	float q10 = quat1[0];
	float q20 = quat2[0];

	float q1g[3] = { quat1[1],quat1[2],quat1[3] };
	float q2g[3] = { quat2[1],quat2[2],quat2[3] };

	float res[4] = { 0,0,0,0 };
	float mult = 0.0f;
	mult = vecMult(q1g, q2g);
	res[0] = q10 * q20- mult;
	float q2gBis[3] = { q10 * q2g[0],q10 * q2g[1],q10 * q2g[2] };
	float q1gBis[3] = { q20 * q1g[0],q20 * q1g[1],q20 * q1g[2] };
	float* semires = cross(q1g, q2g);
	res[1] = { q2gBis[0] + q1gBis[0] + semires[0] };
	res[2] = { q2gBis[1] + q1gBis[1] + semires[1] };
	res[3] = { q2gBis[2] + q1gBis[2] + semires[2] };
	return res;
}
float ModulePhysics::vecMult(float vec1[3], float* vec2)
{
	float res = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		res = res + (vec1[i] * vec2[i]);
	}
	return res;
}
float* ModulePhysics::cross(float vec1[3], float vec2[3])
{
	float res[3] = { (vec2[2] * vec1[1]) - (vec2[1] * vec1[2]),(vec2[0] * vec1[2]) - (vec2[2] * vec1[0]),(vec2[1] * vec1[0]) - (vec2[0] * vec1[1]) };
	return res;
}
