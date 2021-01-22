#include"Fire.h"
#include"Application.h"

Fire::Fire(SDL_Texture* adTexture)
{
	fireTexture = adTexture;

	fireAnimation.PushBack({ 267,62,47,44 });
	fireAnimation.PushBack({ 454,54,61,60 });
	fireAnimation.PushBack({ 637,44,81,80 });
	fireAnimation.PushBack({ 820,36,99,93 });
	fireAnimation.PushBack({ 45,221,111,111 });
	fireAnimation.PushBack({ 232,216,121,122 });

	fireAnimation.PushBack({ 419,212,131,131 });
	fireAnimation.PushBack({ 607,208,137,142 });
	fireAnimation.PushBack({ 796,205,143,149 });
	fireAnimation.PushBack({ 23,396,151,153 });
	fireAnimation.PushBack({ 213,393,156,160 });
	fireAnimation.PushBack({ 401,392,162,164 });

	fireAnimation.PushBack({ 591,391,164,169 });
	fireAnimation.PushBack({ 780,390,168,172 });
	fireAnimation.PushBack({ 10,582,171,173 });
	fireAnimation.PushBack({ 200,581,173,176 });
	fireAnimation.PushBack({ 392,581,172,175 });
	fireAnimation.PushBack({ 582,580,174,176 });

	fireAnimation.PushBack({ 773,581,174,175 });
	fireAnimation.PushBack({ 6,773,174,175 });
	fireAnimation.PushBack({ 198,774,174,173 });
	fireAnimation.PushBack({ 391,774,173,174 });
	fireAnimation.PushBack({ 583,773,174,175 });
	fireAnimation.PushBack({ 774,773,174,175 });

	fireAnimation.PushBack({ 6,965,176,175 });
	fireAnimation.PushBack({ 198,965,174,175 });
	fireAnimation.PushBack({ 390,966,172,174 });
	fireAnimation.PushBack({ 581,967,172,175 });
	fireAnimation.PushBack({ 772,968,173,174 });
	fireAnimation.PushBack({ 4,1161,173,175 });

	fireAnimation.PushBack({ 195,1161,157,175 });
	fireAnimation.PushBack({ 386,1160,158,164 });
	fireAnimation.PushBack({ 578,1161,157,163 });
	fireAnimation.PushBack({ 581,967,172,175 });
	fireAnimation.PushBack({ 768,1161,161,155 });
	fireAnimation.PushBack({ 1,1,5,5 });
	fireAnimation.speed = 0.3f;
	fireAnimation.loop = false;

	currentAnimation = &fireAnimation;
}

void Fire::Draw(Application* app)
{
	SDL_Rect anim = currentAnimation->GetCurrentFrame();
	app->renderer->Blit(fireTexture, metersToPixels(position.x), metersToPixels(position.y), &anim);
}
bool Fire::Start(Application* app)
{
	return true;
}
bool Fire::PreUpdate(Application* app)
{
	
	return true;
}
bool Fire::Update(float dt, Application* app)
{
	currentAnimation->Update();
	return true;
}
bool Fire::PostUpdate(Application* app)
{
	return true;
}
bool Fire::CleanUp(Application* app)
{
	return true;
}