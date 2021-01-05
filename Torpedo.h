#ifndef _TORPEDO_H_
#define _TORPEDO_H_
#include"Body.h"
#include"ModuleRender.h"

class Torpedo : public Body
{
public:
	Torpedo() {}
	~Torpedo() {}
public:
	void Draw(Application* app)override;
	bool Start(Application* app) override;
	bool PreUpdate(Application* app) override;
	bool Update(float dt, Application* app) override;
	bool PostUpdate(Application* app)override;
	bool CleanUp(Application* app)override;


};
#endif
