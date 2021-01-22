#ifndef _FIRE_H_
#define _FIRE_H_
#include"Body.h"
#include"ModuleRender.h"

class Fire : public Body
{
public:
	Fire(SDL_Texture* adTexture);
	~Fire() {}
public:

	void Draw(Application* app)override;
	bool Start(Application* app) override;
	bool PreUpdate(Application* app) override;
	bool Update(float dt, Application* app) override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;

	SDL_Texture* fireTexture;
	Animation fireAnimation;
	Animation* currentAnimation;


};
#endif
