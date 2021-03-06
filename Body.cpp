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
		if (Collider != nullptr) {
			if (Collider->Type != colliderType::player)
			{

				Collider->setPos((bodyRect.w/2) + metersToPixels(position.x) + app->renderer->camera.x, metersToPixels(position.y) + app->renderer->camera.y + (bodyRect.h / 2));
			}
		}
	}
	void Body::Draw(Application* app) {
		//app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	}
	int Body::getXMiddle() {
		return bodySize.x;
	}
	int Body::getYMiddle() {
		return bodySize.y;
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
