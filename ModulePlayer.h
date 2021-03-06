#ifndef _MODULEPLAYER_H_
#define _MODULEPLAYER_H_

#include "Animation.h"
//#include "Globals.h"
#include<string.h>
#include"Body.h"

#include"ModuleRender.h"
enum class playerState {
	Free,Static
};
class ModulePlayer : public Body
{
public:
	Vec2 finalForce;
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
	Animation shipDestroy;
	Animation* currentAnimation;
	void Draw(Application* app)override;
	char text[5] = { "\0" };
	int life;
	int ammo;
	int fuel;
	bool alive;
	bool arcadeMode;
	bool checkColliders(collider* body)override;
	void Collision(collider* bodies, collider* external, Application* app)override;
	collider* base;
	collider* col1;
	collider* col3;
	collider* col4;
	collider* col5;
	collider* col6;
	collider* playerArr [6];
};
#endif