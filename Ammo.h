#ifndef _AMMO_H_
#define _AMMO_H_
#include"Body.h"
#include"ModuleRender.h"

class Ammo : public Body
{
public:
	Ammo(SDL_Texture* adTexture);
	~Ammo() {}
public:

	void Draw(Application* app)override;
	bool Start(Application* app) override;
	bool PreUpdate(Application* app) override;
	bool Update(float dt, Application* app) override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;

	SDL_Texture* ammoTexture;
	Animation ammoAnimation;
	Animation* currentAnimation;


};
#endif
