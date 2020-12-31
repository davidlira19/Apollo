#ifndef _BODY_H_
#define _BODY_H_
#include "Vec2.h"
#include"Animation.h"
#include<math.h>
#include"Collisions.h"

//#include"Application.h"

class Body
{
public:
	Body() 
	{
		pendingToDelete = false;
	}
	~Body() {}
public:
	//Variables
	Vec2 position;
	double rotation;
	float mass;
	bool pendingToDelete;
	Vec2 acceleration;
	Vec2 velocity;
	void setPos() 
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
		Collider->setPos(position.x, position.y);

	}
	virtual void Draw(Application* app){}
	int getXMiddle() {
		return bodyRect.w / 2;
	}
	int getYMiddle() {
		return bodyRect.h / 2;
	}
	SDL_Texture* boodyTexture;
	virtual bool Start(Application* app){
		return true;
	}
	virtual bool PreUpdate(Application* app){
		return true;
	}
	virtual bool Update(float dt, Application* app){
		return true;
	}
	virtual bool PostUpdate(Application* app){
		return true;
	}
	virtual bool CleanUp(Application* app){
		return true;
	}
public:
	Animation* currentAnimation;
	SDL_Rect bodyRect;
	collider* Collider;
	//Methods
	/*void addForce(int force);
	void addMomentum(int momentum);*/
};
#endif