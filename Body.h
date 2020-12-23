#pragma once

class Body
{
public:
	Body();
	~Body();
public:
	//Variables
	Vec2 position;
	double rotation;
	float mass;

public:
	//Methods
	void addForce(int force);
	void addMomentum(int momentum);
};