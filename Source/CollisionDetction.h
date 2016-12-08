#pragma once
#include "Constants.h"
#include <Engine/Sprite.h>

class CollisionDetction 
{
public:
	CollisionDetction()=default;
	~CollisionDetction()=default;
	bool hasThereBeenACollision( float AX, float AY, float AHeight, float AWidth, float BX, float BY, float BHeight, float BWidth);
private:

};
