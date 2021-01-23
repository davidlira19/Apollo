#include"Ammo.h"
#include"Application.h"

Ammo::Ammo(SDL_Texture* adTexture)
{
	ammoTexture = adTexture;

	ammoAnimation.PushBack({ 0,0,79,66 });
	ammoAnimation.PushBack({ 86,0,164-86,71 });
	ammoAnimation.PushBack({ 171,0,245-171,80 });
	ammoAnimation.PushBack({ 332,0,388-332,80 });
	ammoAnimation.PushBack({ 402,0,461-402,79 });

	ammoAnimation.PushBack({ 0,76,66,157-76 });
	ammoAnimation.PushBack({ 85,82,157-85,161-82 });
	ammoAnimation.PushBack({ 171,82,247-171,156-82 });
	ammoAnimation.PushBack({ 254,83,334-254,150-83 });
	ammoAnimation.PushBack({ 345,86,427-345,142-86 });

	ammoAnimation.PushBack({ 5,169,86-5,228-169 });
	ammoAnimation.PushBack({ 95,167,176-95,235-167 });
	ammoAnimation.PushBack({ 182,164,260-182,236-164 });
	ammoAnimation.PushBack({ 265,154,340-265,232-154 });
	ammoAnimation.PushBack({ 354,152,421-354,232-152 });

	ammoAnimation.PushBack({ 11,240,67-11,323-240 });
	ammoAnimation.PushBack({ 94,242,153-94,323-242 });
	ammoAnimation.PushBack({ 158,240,226-158,320-240 });
	ammoAnimation.PushBack({ 236,240,308-236,319-240 });
	ammoAnimation.PushBack({ 316,243,393-316,319-243 });
	ammoAnimation.PushBack({ 405,249,486-405,316-249 });

	ammoAnimation.PushBack({ 2,330,84-2,387-330 });
	ammoAnimation.PushBack({ 102,328,183-102,388-328 });

	ammoAnimation.speed = 0.2f;
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