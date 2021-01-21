#include"BodyManager.h"
#include"Application.h"
bodyManager::bodyManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}
bodyManager::~bodyManager() {

}

bool bodyManager::Start() 
{
	//fireText = App->textures->Load("Assets/Textures/fire.png");
	Texture = App->textures->Load("Assets/Textures/spaceShooter2_spritesheet.png");
	Texture1 = App->textures->Load("Assets/Textures/ship.png");
	Texture2 = App->textures->Load("Assets/Textures/earth.png");
	Texture3 = App->textures->Load("Assets/Textures/moon.png");
	playerLose = false;
	count = false;
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
			auxiliar = auxiliar->next;
			delete auxiliar->prev->data;
			bodyList.del(auxiliar->prev);

		}
		else {
			auxiliar = auxiliar->next;
		}

	}
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{
		auxiliar->data->setPos(App);
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
	if (playerLose == true && count == false && App->scene->player->shipDestroy.HasFinished() == true) 
	{
		App->fade->FadeToBlack(this, App->scene_lose);
		count = true;
		
	}
	return UPDATE_CONTINUE;
}
bool bodyManager::CleanUp() 
{
	
	App->textures->Unload(Texture);
	App->textures->Unload(Texture1);
	App->textures->Unload(Texture2);
	App->textures->Unload(Texture3);
	p2List_item<Body*>* auxiliar;
	p2List_item<Body*>* auxiliar1;
	auxiliar = bodyList.getFirst();
	while (auxiliar != nullptr)
	{		
		auxiliar1 = auxiliar->next;
		delete auxiliar->data;
		bodyList.del(auxiliar);
		auxiliar = nullptr;
		auxiliar = auxiliar1;
	}
	App->scene->Disable();
	return true;
}
Asteroid* bodyManager::CreateAsteroid(Vec2 pos,int rad, double rotation, float mass, int life, int ammo, float fuel, Vec2 acceleration, Vec2 velocity)
{
	Asteroid* rocket = new Asteroid();
	rocket->position.x = pixelsToMeters(pos.x);
	rocket->position.y = pixelsToMeters(pos.y);
	rocket->rotation = rotation;
	rocket->mass = mass;
	rocket->type = bodyType::Asteroid;
	rocket->acceleration = acceleration;
	rocket->velocity = velocity;
	rocket->boodyTexture = Texture;
	rocket->bodyRect = {0,132,73,74};
	rocket->Collider= App->collisions->addCollider(rad, colliderType::roket, this, pos.x, pos.y);
	App->scene->asteroids++;

	bodyList.add(rocket);

	return rocket;
}
Planet* bodyManager::CreatePlanet(Vec2 pos,int type, int rad, float mass, float radius, Vec2 localGravity)
{
	Planet* planet = new Planet();
	planet->position.x = pixelsToMeters(pos.x);
	planet->position.y = pixelsToMeters(pos.y);
	planet->mass = mass;
	planet->radius = radius;
	planet->localGravity = localGravity;
	planet->type = bodyType::Planet;
	switch (type)
	{
	case 1:
		planet->boodyTexture = Texture2;
		planet->bodyRect = { 0,0,800,800 };
		break;
	case 2:
		planet->boodyTexture = Texture3;
		planet->bodyRect = { 0,0,600,600 };
		break;
	}
	//planet->boodyTexture = Texture;
	planet->Collider=App->collisions->addCollider(rad, colliderType::planet, this, pos.x, pos.y);
	bodyList.add(planet);
	return planet;
}

Torpedo* bodyManager::CreateTorpedo(Vec2 pos, Vec2 velocity, double rotation, Vec2 acceleration)
{
	Torpedo* torpedo = new Torpedo();
	torpedo->position.x = pos.x;
	torpedo->position.y = pos.y;
	torpedo->acceleration = acceleration;
	torpedo->velocity = velocity;
	torpedo->rotation = rotation;
	torpedo->boodyTexture = Texture;
	torpedo->bodyRect = { 319,139,12,48 };
	torpedo->Collider = App->collisions->addRectCollider(torpedo->bodyRect, colliderType::torpedo, this, pos.x, pos.y);
	bodyList.add(torpedo);

	return torpedo;
}

ModulePlayer* bodyManager::CreatePlayer(Vec2 pos, float mass)
{
	ModulePlayer* player = new ModulePlayer(Texture1);
	player->position.x = pixelsToMeters(pos.x);
	player->position.y = pixelsToMeters(pos.y);
	
	player->mass = mass;
	//player->boodyTexture = Texture;
	player->bodyRect = { 186,215,40,103 };
	player->type = bodyType::Player;
	player->col1 = App->collisions->addCollider(20, colliderType::player, this, pos.x, pos.y);
	player->base = App->collisions->addCollider(20, colliderType::player, this, pos.x, pos.y);
	player->col3 = App->collisions->addCollider(10, colliderType::player, this, pos.x, pos.y);
	player->col4 = App->collisions->addCollider(10, colliderType::player, this, pos.x, pos.y);
	player->col5 = App->collisions->addCollider(10, colliderType::player, this, pos.x, pos.y);
	player->col6 = App->collisions->addCollider(10, colliderType::player, this, pos.x, pos.y);
	player->playerArr[0] = player->base;
	player->playerArr[1] = player->col1;
	player->playerArr[2] = player->col3;
	player->playerArr[3] = player->col4;
	player->playerArr[4] = player->col5;
	player->playerArr[5] = player->col6;
	//App->collisions->addCollider(20, colliderType::player, this, pos.x, pos.y);
	bodyList.add(player);
	return player;
}


void bodyManager::OnCollision(collider* body1, collider* body2,Application* app)
{ 
	if (playerLose == false)
	{
		p2List_item<Body*>* auxiliar1 = nullptr;
		p2List_item<Body*>* auxiliar2 = nullptr;
		auxiliar2 = app->bodyesManager->bodyList.getFirst();
		auxiliar1 = app->bodyesManager->bodyList.getFirst();

		while (auxiliar1 != nullptr)
		{
			if (auxiliar1->data->checkColliders(body1) == true)
			{
				break;
			}
			auxiliar1 = auxiliar1->next;
		}
		while (auxiliar2 != nullptr)
		{
			if (auxiliar2->data->checkColliders(body2) == true)
			{
				break;
			}
			auxiliar2 = auxiliar2->next;
		}
		if ((body1->Type == colliderType::planet && body2->Type == colliderType::player) || (body1->Type == colliderType::player && body2->Type == colliderType::planet))
		{
			if (body1->Type == colliderType::player && body2->Type == colliderType::planet)
			{
				auxiliar1->data->Collision(body1, body2, app);
			}

			if (auxiliar1->data->type == bodyType::Planet && metersToPixels(auxiliar1->data->position.y)  == -12500 && app->scene->asteroids <= 1)
			{
				
				app->scene->canWin = true;
			}
			else if (auxiliar1->data->type == bodyType::Planet && metersToPixels(auxiliar1->data->position.y)  == 1900 && app->scene->canWin == true)
			{
				auxiliar1->data->pendingToDelete = true;
				App->fade->FadeToBlack(this, App->scene_win);
			}
			if (auxiliar2->data->type == bodyType::Planet && metersToPixels(auxiliar2->data->position.y) == -12500 && app->scene->asteroids <= 1)
			{
				app->scene->canWin = true;
			}
			else if (auxiliar2->data->type == bodyType::Planet && metersToPixels(auxiliar2->data->position.y) == 1900 && app->scene->canWin == true)
			{
				auxiliar2->data->pendingToDelete = true;
				App->fade->FadeToBlack(this, App->scene_win);
			}
		}
		if ((body1->Type == colliderType::torpedo && body2->Type == colliderType::roket) || (body1->Type == colliderType::roket && body2->Type == colliderType::torpedo))
		{
			if (auxiliar1->data->type == bodyType::Asteroid)
			{
				auxiliar1->data->pendingToDelete = true;
				App->scene->asteroids--;
				App->audio->PlayFx(App->scene->destroyFx);
			}
			if (auxiliar2->data->type == bodyType::Asteroid)
			{
				auxiliar2->data->pendingToDelete = true;
				App->scene->asteroids--;
				App->audio->PlayFx(App->scene->destroyFx);
			}
		}
		if ((body1->Type == colliderType::player && body2->Type == colliderType::roket) || (body1->Type == colliderType::roket && body2->Type == colliderType::player))
		{
			if (auxiliar1->data->type == bodyType::Player)
			{
				auxiliar2->data->pendingToDelete = true;
				playerLose = true;
				App->scene->player->alive = false;
				App->audio->PlayFx(App->scene->destroyFx);
			}
			if (auxiliar2->data->type == bodyType::Player)
			{
				auxiliar1->data->pendingToDelete = true;
				playerLose = true;
				App->scene->player->alive = false;
				App->audio->PlayFx(App->scene->destroyFx);
			}
		}
	}
}