#include"Asteroid.h"
#include"Application.h"
void Asteroid::Draw(Application* app)
{
	
	app->renderer->Blit(boodyTexture, metersToPixels(position.x), metersToPixels(position.y), &bodyRect, 1, 1, rotation, getXMiddle(), getYMiddle());
}
bool Asteroid::Start(Application* app) {
	return true;
}
bool Asteroid::PreUpdate(Application* app) {
	Body::PreUpdate(app);
	return true;
}
bool Asteroid::Update(float dt, Application* app) {
	
	position.x +=pixelsToMeters(0.5f);


	
	return true;
	
}
bool Asteroid::PostUpdate(Application* app) {
	return true;
}
bool Asteroid::CleanUp(Application* app) {
	return true;
}