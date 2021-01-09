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
		/*float posX = position.x + getXMiddle();
		float posY = position.y + getYMiddle();
		float ang = ((rotation * M_PI) / 180);
		float respX = Collider->position.x- posX;
		float respY = Collider->position.y- posY;
		float totalResp = sqrt((respX * respX) + (respY * respY));
		float res = totalResp * sin(ang/2);
		res = res * 2;
		float finalPositionY = Collider->position.y + (res * sin(ang));
		float finalPositionX = Collider->position.x + (res * cos(ang));
		Collider->setPos(finalPositionX+ respX, finalPositionY+ respY);*/
		if (Collider->Type != colliderType::player) 
		{
			Collider->setPos(getXMiddle()+position.x +app->renderer->camera.x , position.y +app->renderer->camera.y + getYMiddle());
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
