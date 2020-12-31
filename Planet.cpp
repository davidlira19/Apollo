#include"Planet.h"
#include"Application.h"
Planet::Planet() {}
Planet::~Planet() {}
bool Planet::Start(Application* app) {
	return true;
}
bool Planet::PreUpdate(Application* app)  {
	return true;
}
bool Planet::Update(float dt, Application* app)  {
	return true;
}
bool Planet::PostUpdate(Application* app)  {
	return true;
}
bool Planet::CleanUp(Application* app){
	return true;
}
void Planet::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
}