#include"Body.h"
#include"Application.h"
#include"ModuleRender.h"
	Body::Body()
	{
		pendingToDelete = false;
	}
	Body::~Body()
	{
		if (Collider != nullptr) 
		{ 
			Collider->toDelete = true; 
		}
	}

	//Variables
	void Body::setPos(Application* app)
	{
		if (Collider->Type != colliderType::player) 
		{
			
			Collider->setPos(getXMiddle()+ metersToPixels(position.x) +app->renderer->camera.x , metersToPixels(position.y)  +app->renderer->camera.y + getYMiddle());
		}
		//Collider->setPos(position.x + getXMiddle(), position.y + getYMiddle());
	}
	void Body::Draw(Application* app) {
		//app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	}
	int Body::getXMiddle() {
		return bodyRect.w / 2;
	}
	int Body::getYMiddle() {
		return bodyRect.h / 2;
	}

	bool Body::Start(Application* app) {
		return true;
	}
	bool Body::PreUpdate(Application* app) {
		if (position.x < 5 )
		{
			position.x = 40 ;
		}
		else if (position.x > 41)
		{
			position.x = 6;
		}
		return true;
	}
	bool Body::Update(float dt, Application* app) {
		return true;
	}
	bool Body::PostUpdate(Application* app) {
		return true;
	}
	bool Body::CleanUp(Application* app) {
		return true;
	}

	void Body::Collision(collider* bodies, collider* external, Application* app) {

	}
	bool Body::checkColliders(collider* body) {
		if (body == Collider) {
			return true;
		}
		else {
			return false;
		}
	}
	//Methods
	/*void addForce(int force);
	void addMomentum(int momentum);*/
