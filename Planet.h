#ifndef _PLANET_H_
#define _PLANET_H_
#include"Body.h"
#include"ModuleRender.h"
class Planet : public Body
{
public:
	Planet();
	~Planet();
	bool Start(Application* app)override;
	bool PreUpdate(Application* app) override;
	bool Update(float dt, Application* app) override;
	bool PostUpdate(Application* app) override;
	bool CleanUp(Application* app) override;
	void Draw(Application* app)override;
public:
	float radius;
	Vec2 localGravity;

};
#endif