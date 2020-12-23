#pragma once

class Planet : public Body
{
public:
	Planet();
	~Planet();
public:
	float radius;
	Vec2 localGravity;
};