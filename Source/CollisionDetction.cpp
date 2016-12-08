#include "CollisionDetction.h"
#include <Engine/Sprite.h>

bool CollisionDetction::hasThereBeenACollision(float AX, float AY, float AHeight, float AWidth, float BX, float BY, float BHeight, float BWidth)
{
		if ((AX + AWidth) >= (BX) && (AX) <= (BX + BWidth) && (AY + AHeight) >= (BY) && (AY) <= (BY + BHeight))
		{
			return true;
		}
	return false;
}