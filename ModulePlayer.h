#ifndef _MODULEPLAYER_H_
#define _MODULEPLAYER_H_

#include "Animation.h"
//#include "Globals.h"

#include"Body.h"

#include"ModuleRender.h"
class ModulePlayer : public Body
{
public:
	ModulePlayer(SDL_Texture* adTexture);
	virtual ~ModulePlayer();
	bool Start(Application* app)override;
	bool PreUpdate(Application* app)override;
	bool Update(float dt, Application* app)override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;
	void launchTorpedo();
	SDL_Texture* fire;
	Animation fireAnimation;
	Animation* currentAnimation;
	void Draw(Application* app)override;
	int life;
	int ammo;
	int fuel;
};
#endif