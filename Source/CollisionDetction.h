#pragma once
#include "Constants.h"
#include "Actor.h"
#include <Engine/Sprite.h>

class CollisionDetction 
{
public:
	CollisionDetction(std::vector<Actor*>& obj);
	~CollisionDetction()=default;

	void Tick();
	bool hasThereBeenACollision(Actor* A, Actor* B);

private:
	int distanceThreshold = 100;
	std::vector<Actor*> gameObjs;
};
