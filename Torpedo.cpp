#include"Torpedo.h"
#include"Application.h"
void Torpedo::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, metersToPixels(position.x), metersToPixels(position.y) , &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
	
}
bool Torpedo::Start(Application* app) 
{
	return true;
}
bool Torpedo::PreUpdate(Application* app) 
{
	return true;
}
bool Torpedo::Update(float dt, Application* app) 
{
	position.x += velocity.x*0.036;
	position.y += velocity.y * 0.036;
	return true;
}
bool Torpedo::PostUpdate(Application* app) 
{
	return true;
}
bool Torpedo::CleanUp(Application* app) 
{
	return true;
}