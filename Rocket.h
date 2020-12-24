#pragma once

class Rocket : public Body
{
public:
	Rocket() {}
	~Rocket() {}
public:
	int life;
	int ammo;
	Vec2 acceleration;
	Vec2 velocity;
	float force;
	SDL_Texture* rocketTexture;
};