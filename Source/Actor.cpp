#include"Actor.h"
#include "Constants.h"

#include<vector>
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

bool Actor::hasSpriteHitLeftWall(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite)
{
	if(ActorSprite[i]->position[0]==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Actor::hasSpriteHitRightWall(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite)
{
	if (ActorSprite[i]->position[0] == WINDOW_WIDTH - 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Actor::MoveRight(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite, int speed)
{
	ActorSprite[i]->position[0] += speed;
}
void Actor::MoveLeft(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite, int speed)
{
	ActorSprite[i]->position[0] -= speed;
}



//void Actor::killSprite(int i)
//{
//	ActorSprite[i] = nullptr;
//}
//float Actor::GetXpostion(int i)
//{
//	Xpos = Bullet->position[0];
//	return Xpos;
//}
//float Actor::GetYpostion(int i)
//{
//	Ypos = Bullet->position[1];
//	return Ypos;
//}
