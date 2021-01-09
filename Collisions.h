#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include"Vec2.h"
#include "p2List.h"
#include "Module.h"
//#include"Application.h"
#include"SDL/include/SDL.h"
enum class colliderType {
	player, roket,planet, torpedo
};
class collider {
public:
	collider(int rad, colliderType type, Module* Lisener, int x, int y) 
	{
		circleRad = rad;
		Type = type;
		lisener = Lisener;
		position.x = x;
		position.y = y;
		toDelete = false;
	}
	collider(SDL_Rect rect, colliderType type, Module* Lisener, int x, int y)
	{
		rectCollider = rect;
		Type = type;
		lisener = Lisener;
		position.x = x;
		position.y = y;
		toDelete = false;
	}
	~collider() 
	{

	}
	//private:
	int circleRad;
	SDL_Rect rectCollider;
	bool toDelete;
	Vec2 position;
	colliderType Type;
	Module* lisener;
	void setPos(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	bool intersect(collider* vec1)
	{

		float respX = this->position.x - vec1->position.x;
		float respY = this->position.y - vec1->position.y;
		float totalResp = sqrt((respX * respX) + (respY * respY));
		if (totalResp <= this->circleRad + vec1->circleRad) {
			return true;
		}
		else {
			return false;
		}
	}

};
class collision :public Module 
{
public:
	collision(Application* app, bool start_enabled) : Module(app, start_enabled) 
	{

	}
	p2List<collider*> colliderList;
	collider* addCollider(int rad, colliderType type, Module* Lisener, int x, int y) 
	{
		collider* node = new collider(rad, type, Lisener, x, y);
		colliderList.add(node);
		return node;
	}
	collider* addRectCollider(SDL_Rect rect, colliderType type, Module* Lisener, int x, int y)
	{
		collider* node = new collider(rect, type, Lisener, x, y);
		colliderList.add(node);
		return node;
	}
	update_status PreUpdate()override 
	{
		p2List_item<collider*>* auxiliar1;
		p2List_item<collider*>* auxiliar;
		auxiliar = colliderList.getFirst();
		while (auxiliar != nullptr)
		{
			if (auxiliar->data->toDelete == true)
			{
				auxiliar1 = auxiliar->next;
				delete auxiliar->data;
				colliderList.del(auxiliar);
				auxiliar = nullptr;
				auxiliar = auxiliar1;
			}
			else 
			{
				auxiliar = auxiliar->next;
			}
		
		}

		return UPDATE_CONTINUE;
	}

	update_status Update(float dt)override {
		p2List_item<collider*>* auxiliar1;
		p2List_item<collider*>* auxiliar2;
		auxiliar1 = colliderList.getFirst();
		while (auxiliar1 != nullptr)
		{
			auxiliar2 = auxiliar1->next;
			while (auxiliar2 != nullptr)
			{
				if (auxiliar1->data->Type != auxiliar2->data->Type)
				{
					if (auxiliar1->data->intersect(auxiliar2->data) == true) {
						auxiliar1->data->lisener->OnCollision(auxiliar1->data, auxiliar2->data,App);
					}
				}
				auxiliar2 = auxiliar2->next;

			}
			auxiliar1 = auxiliar1->next;
		}
		return UPDATE_CONTINUE;
	}
	update_status PostUpdate()override
	{
		
		return UPDATE_CONTINUE;
	}
};
#endif
