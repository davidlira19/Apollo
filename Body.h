#ifndef _BODYH
#define _BODYH
#include "Vec2.h"
#include"Animation.h"
#include<math.h>
#include"Collisions.h"

//#include"Application.h"
enum class bodyType 
{
	Planet,Player,Asteroid,Torpedo
};
class Body
{
public:
    Body();
    virtual ~Body();
public:
    //Variables
	bodyType type;
    Vec2 position;
    double rotation;
    float mass;
    bool pendingToDelete;
    Vec2 acceleration;
    Vec2 velocity;
	float angularVelocity;
    virtual void setPos(Application* app);
    virtual void Draw(Application* app);
    int getXMiddle();
    int getYMiddle();
    SDL_Texture* boodyTexture;
	virtual bool checkColliders(collider* body);
	virtual void Collision(collider* bodies, collider* external, Application* app);
    virtual bool Start(Application* app);
    virtual bool PreUpdate(Application* app);
    virtual bool Update(float dt, Application* app);
    virtual bool PostUpdate(Application* app);
    virtual bool CleanUp(Application* app);
public:
    Animation* currentAnimation;
    SDL_Rect bodyRect;
    collider* Collider;
    //Methods
    void addForce(int force);
    void addMomentum(int momentum);
};
#endif