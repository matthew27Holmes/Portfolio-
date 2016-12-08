#include "Barrier.h"
#include <Engine/Sprite.h>
#include <Engine/Input.h>
#include <Engine/Keys.h>

Barrier::Barrier()
{
	health.resize(3);
	for (int i=0; i < health.size(); i++)
	{
		health[i] = 10;
	}
	//isAlive = true;
	Blocks.reserve(3);
	for (int i = 0; i < Blocks.size(); i++)
	{
		Blocks.push_back(std::move(Barriers));
	}
	deadBarriers.resize(3);
}
void Barrier::Reset()
{
	for (int i = 0; i < deadBarriers.size(); i++)
	{
		deadBarriers[i] = false;
		health[i] = 10;
	}
}
bool Barrier::init(std::shared_ptr<ASGE::Renderer> renderer)
{
	Blocks.resize(3);
	int x = 100;
	int addonForNextSprite = 0;
	for (int i = 0; i < Blocks.size(); i++)
	{
		Blocks[i] = renderer->createSprite();
		Blocks[i]->position[0] = x+addonForNextSprite;
		Blocks[i]->position[1] = 530;
		if (!Blocks[i]->loadTexture("..\\..\\Resources\\Textures\\Barrier.PNG"))
		{
			return false;
		}
		Blocks[i]->size[0] = 100;
		Blocks[i]->size[1] = 55;
		addonForNextSprite += 400;
	}
}
void Barrier::deleteBarrier(int i )
{
	deadBarriers[i] = true;
}
void Barrier::TakeDamge(int i)
{
 	health[i]-=2;
	if (health[i] <= 0)
	{
		deleteBarrier(i);
	}
}
float Barrier::GetWidth(int i)
{
	Width = Blocks[i]->size[0];
	return Width;
}
float Barrier::Gethight(int i)
{
	Height = Blocks[i]->size[1];
	return Height;
}
float Barrier::GetBarrierY(int i)
{
	Ypos = Blocks[i]->position[1];
	return Ypos;
}
float Barrier::GetBarrierX(int i)
{
	Xpos = Blocks[i]->position[0];
	return Xpos;
}
int Barrier::getHealth(int i)
{
	return health[i];
}
void Barrier::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i = 0; i < 3; i++)
	{
		if (!deadBarriers[i])
		{
			Blocks[i]->render(renderer);
		}
	}
}