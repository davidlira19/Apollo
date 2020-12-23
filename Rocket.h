#pragma once

class Rocket : public Body
{
public:
	Rocket();
	~Rocket();
public:
	int life;
	Vec2 acceleration;
	Vec2 velocity;
	float force;
};
