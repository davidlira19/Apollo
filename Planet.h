#pragma once
#include"Body.h"
#include"ModuleRender.h"
class Planet : public Body
{
public:
	Planet() {}
	~Planet() {}
	bool Start(Application* app)override {
		return true;
	}
	bool PreUpdate(Application* app) override {
		return true;
	}
	bool Update(float dt, Application* app) override {
		return true;
	}
	bool PostUpdate(Application* app) override {
		return true;
	}
	bool CleanUp(Application* app) override {
		return true;
	}
	void Draw(Application* app)override
	{
		//app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	}
public:
	float radius;
	Vec2 localGravity;

};