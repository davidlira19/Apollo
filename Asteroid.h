#ifndef _ASTEROID_H_
#define _ASTEROID_H_
#include"Body.h"
#include"ModuleRender.h"

class Asteroid : public Body
{
public:
	Asteroid() {}
	~Asteroid() {}
public:

	float force;
public:

	void Draw(Application* app)override;
	bool Start(Application* app) override;
	bool PreUpdate(Application* app) override;
	bool Update(float dt, Application* app) override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;


};
#endif
