#include"BodyManager.h"
#include"Application.h"
bodyManager::bodyManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}
bodyManager::~bodyManager() {

}
void bodyManager::OnCollision(collider* body1, collider* body2) 
{

}
bool bodyManager::Start() 
{
	fireText = App->textures->Load("Assets/Textures/fire.png");
	Texture=App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	return true;
}
update_status bodyManager::PreUpdate() 
{
	p2List_item<Body*>* auxiliar;
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		if (auxiliar->data->pendingToDelete == true)
		{
			delete auxiliar->data;
			bodyList.del(auxiliar);
		}
		auxiliar = auxiliar->next;
	}
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->setPos();
		auxiliar = auxiliar->next;
	}
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->PreUpdate(App);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
update_status bodyManager::Update(float dt) 
{
	p2List_item<Body*>* auxiliar;
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->Update(dt, App);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
update_status bodyManager::PostUpdate() 
{
	p2List_item<Body*>* auxiliar;
	
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->PostUpdate(App);
		auxiliar = auxiliar->next;
	}
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->Draw(App);
		auxiliar = auxiliar->next;
	}
	return UPDATE_CONTINUE;
}
bool bodyManager::CleanUp() 
{
	App->textures->Unload(Texture);
	return true;
}
Asteroid* bodyManager::CreateAsteroid(Vec2 pos,int rad, double rotation, float mass, int life, int ammo, float fuel, Vec2 acceleration, Vec2 velocity)
{
	Asteroid* rocket = new Asteroid();
	rocket->position = pos;
	rocket->rotation = rotation;
	rocket->mass = mass;
	rocket->acceleration = acceleration;
	rocket->velocity = velocity;
	rocket->boodyTexture = Texture;
	rocket->bodyRect = {0,132,73,74};
	rocket->Collider= App->collisions->addCollider(rad, colliderType::roket, this, pos.x, pos.y);
	
	bodyList.add(rocket);

	return rocket;
}
Planet* bodyManager::CreatePlanet(Vec2 pos, int rad, float mass, float radius, Vec2 localGravity)
{
	Planet* planet = new Planet();
	planet->position = pos;
	planet->mass = mass;
	planet->radius = radius;
	planet->localGravity = localGravity;
	planet->boodyTexture = Texture;
	planet->Collider=App->collisions->addCollider(rad, colliderType::planet, this, pos.x, pos.y);
	bodyList.add(planet);
	return planet;
}
ModulePlayer* bodyManager::CreatePlayer(Vec2 pos, float mass)
{
	ModulePlayer* player = new ModulePlayer(fireText);
	player->position = pos;
	player->mass = mass;
	player->boodyTexture = Texture;
	player->bodyRect = { 186,215,42,124 };
	player->Collider=App->collisions->addCollider(45, colliderType::player, this, pos.x, pos.y);
	//App->collisions->addCollider(20, colliderType::player, this, pos.x, pos.y);
	bodyList.add(player);
	return player;
}


void OnCollision(collider* body1, collider* body2,Application* app)
{ 

}