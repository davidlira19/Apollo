#ifndef _MODULEPLAYER_H_
#define _MODULEPLAYER_H_

#include "Animation.h"
//#include "Globals.h"

#include"Body.h"

#include"ModuleRender.h"
enum class playerState {
	Free,Static
};
class ModulePlayer : public Body
{
public:
	playerState state;
	ModulePlayer(SDL_Texture* adTexture);
	virtual ~ModulePlayer();
	bool Start(Application* app)override;
	bool PreUpdate(Application* app)override;
	bool Update(float dt, Application* app)override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;
	void launchTorpedo(Application* app);
	void setPos(Application* app) override;
	SDL_Texture* ship;
	Animation fireAnimation;
	Animation stopAnimation;
	Animation* currentAnimation;
	void Draw(Application* app)override;
	int life;
	int ammo;
	int fuel;
	bool checkColliders(collider* body)override;
	void Collision(collider* bodies, collider* external, Application* app)override;
	collider* col1;
	collider* base;
	collider* col3;
	collider* col4;
	collider* col5;
	collider* col6;
};
#endif