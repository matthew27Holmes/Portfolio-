#include "CollisionDetction.h"
#include <Engine/Sprite.h>



CollisionDetction::CollisionDetction(std::vector<Actor*>& obj)
	: gameObjs(obj){}

void CollisionDetction::Tick()
{
	for (Actor*A : gameObjs)
	{
		if (A->getAlive())
		{
			for (Actor*B : gameObjs)
			{
				if (B->getAlive())
				{
					if (A->getPos().Distance(B->getPos()) < distanceThreshold)
					{
						if (hasThereBeenACollision(A, B))
						{					
							A->handleCollisons(B->getTag());
							B->handleCollisons(A->getTag());
						}
					}
				}
			}
		}
	}
}

bool CollisionDetction::hasThereBeenACollision(Actor* A, Actor* B)
{
	Vector2 aPos = A->getPos();
	Vector2 aSize = A->getSize();
	Vector2 bPos = B->getPos();
	Vector2 bSize = B->getSize();

	if ((aPos.x + aSize.x) >= (bPos.x) && (aPos.x) <= (bPos.x + bSize.x) && (aPos.y + aSize.y) >= (bPos.y) && (aPos.y) <= (bPos.y + bSize.y))
	{
		return true;
	}
	return false;
}