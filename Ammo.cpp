#include"Ammo.h"
#include"Application.h"

Ammo::Ammo(SDL_Texture* adTexture)
{
	ammoTexture = adTexture;

	ammoAnimation.PushBack({ 16,20,107,107 });
	ammoAnimation.PushBack({ 169,6,107,107 });
	ammoAnimation.PushBack({ 331,4,107,107 });
	ammoAnimation.PushBack({ 486,12,107,107 });
	ammoAnimation.PushBack({ 611,22,107,107 });
	ammoAnimation.PushBack({ 742,30,107,107 });

	ammoAnimation.PushBack({ 17,159,107,107 });
	ammoAnimation.PushBack({ 165,150,107,107 });
	ammoAnimation.PushBack({ 335,152,107,107 });
	ammoAnimation.PushBack({ 488,151,107,107 });
	ammoAnimation.PushBack({ 598,150,107,107 });
	ammoAnimation.PushBack({ 741,161,107,107 });

	ammoAnimation.speed = 0.15f;
	ammoAnimation.loop = true;
	
	currentAnimation = &ammoAnimation;
}

void Ammo::Draw(Application* app)
{
	SDL_Rect anim = currentAnimation->GetCurrentFrame();
	app->renderer->Blit(ammoTexture, metersToPixels(position.x), metersToPixels(position.y),&anim);
}
bool Ammo::Start(Application* app)
{
	app->scene->player->ammo = 30;
	return true;
}
bool Ammo::PreUpdate(Application* app)
{
	Body::PreUpdate(app);
	return true;
}
bool Ammo::Update(float dt, Application* app)
{
	currentAnimation->Update();
	return true;
}
bool Ammo::PostUpdate(Application* app)
{
	return true;
}
bool Ammo::CleanUp(Application* app)
{
	return true;
}