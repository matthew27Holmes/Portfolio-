#include"Actor.h"
//#include "Constants.h"

//#include<vector>
//#include <Engine/Input.h>
//#include <Engine/Keys.h>
//#include <Engine/Sprite.h>

Actor::Actor(std::shared_ptr<ASGE::Renderer> renderer)
{
	Sprite = renderer->createSprite();
	alive = true;
	setTag(ObjTags::Act);
}

void Actor::addToObjList(std::vector<Actor*>& obj)
{
	obj.emplace_back(this);
}

bool Actor::LoadSprite(char * spriteName)
{
	if (!Sprite->loadTexture(spriteName))
	{
		std::cout << "error loading sprite " << spriteName <<std::endl;
		return false;
	}
	return true;
}

void Actor::Tick(float dt)
{
	if (alive)
	{
		Sprite->position[0] = Pos.x;
		Sprite->position[1] = Pos.y;
		Sprite->size[0] = Size.x;
		Sprite->size[1] = Size.y;
	}
}

void Actor::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	if (alive)
	{
		Sprite->render(renderer);
	}
}

bool Actor::hasSpriteHitLeftWall()
{
	if(Pos.x <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Actor::hasSpriteHitRightWall()
{
	if (Pos.x >= WINDOW_WIDTH - 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Actor::MoveHorizontally(float dt, float velocity)
{
	Pos.x += (velocity*speed)*dt;
}

void Actor::killSprite()
{
	alive = false;
	//Sprite.reset();
	//Sprite = nullptr;
}