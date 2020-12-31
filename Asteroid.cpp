#include"Asteroid.h"
#include"Application.h"
void Asteroid::Draw(Application* app)
{
	app->renderer->Blit(boodyTexture, position.x, position.y, &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
}
bool Asteroid::Start(Application* app) {
	return true;
}
bool Asteroid::PreUpdate(Application* app) {
	return true;
}
bool Asteroid::Update(float dt, Application* app) {
	return true;
}
bool Asteroid::PostUpdate(Application* app) {
	return true;
}
bool Asteroid::CleanUp(Application* app) {
	return true;
}