#include "Barrier.h"

Barrier::Barrier(Vector2 pos, Vector2 size, std::shared_ptr<ASGE::Renderer> renderer):Actor(renderer)
{
	alive = true;
	health = 10;
	Pos = pos;
	Size = size;
	setTag(ObjTags::Barr);
}

void Barrier::handleCollisons(ObjTags tag)
{
	if (tag == ObjTags::Bull || tag == ObjTags::EmyBull)
	{
		TakeDamge();
	}
	else if (tag == ObjTags::Emy)
	{
		health = 0;
		TakeDamge();
	}
}

void Barrier::Reset()
{
	alive = true;
	health = 10;
}

void Barrier::TakeDamge()
{
 	health -=2;
	if (health <= 0)
	{
		alive = false;
	}
}

int Barrier::getHealth()
{
	return health;
}