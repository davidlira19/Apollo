#pragma once

class Rocket : public Body
{
public:
	Rocket() {}
	~Rocket() {}
public:
	int life;
	int ammo;
	int fuel;
	Vec2 acceleration;
	Vec2 velocity;
	float force;
	SDL_Texture* rocketTexture;
public:
	void launchTorpedo()
	{
		if (ammo > 0)
		{
			ammo -= 1;
		}
	}
};
