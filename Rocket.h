#pragma once
#include"Body.h"
#include"ModuleRender.h"
class Rocket : public Body
{
public:
	Rocket() {}
	~Rocket() {}
public:
	
	float force;

public:
	void Draw(Application* app)override
	{
		//app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	}
	bool Start(Application* app) override {
		return true;
	}
	bool PreUpdate(Application* app) override {
		return true;
	}
	bool Update(float dt, Application* app) override {
		return true;
	}
	bool PostUpdate(Application* app)override {
		return true;
	}
	bool CleanUp(Application* app)override {
		return true;
	}
	

};
