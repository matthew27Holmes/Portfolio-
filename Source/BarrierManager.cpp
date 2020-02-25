#include "BarrierManager.h"

BarrierManager::BarrierManager(std::shared_ptr<ASGE::Renderer> renderer)
{
	Barriers.reserve(3);
	float x = 0;

	for (int i = 0; i < 3; i++)
	{
		x = i == 0 ? 0 : i == 1 ? WINDOW_WIDTH / 2-30 : WINDOW_WIDTH -100;
		Barriers.emplace_back(std::make_unique<Barrier>(Vector2{ x , WINDOW_HEIGHT/1.3 /*530*/ }, Vector2{ 100,55 }, renderer));
		if (!Barriers[i]->LoadSprite("..\\..\\Resources\\Textures\\Barrier.PNG"))
		{
			std::cout << "failed to create barriers";
		}
	
		//x += WINDOW_WIDTH/2;//400
	}
}

void BarrierManager::addToObjList(std::vector<Actor*>&obj)
{
	for (int i = 0; i < (int)Barriers.size(); i++)
	{
		Barriers[i]->addToObjList(obj);
	}
}

void BarrierManager::Tick(float dt)
{
	for (int i = 0; i < (int)Barriers.size(); i++)
	{
		Barriers[i]->Tick(dt);
	}
}

void BarrierManager::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i = 0; i < (int)Barriers.size(); i++)
	{
		if (Barriers[i]->getAlive())
		{
			Barriers[i]->Render(renderer);
		}
	}
}

Barrier* BarrierManager::getBarrier(int i)
{
	return Barriers[i].get();
}


void BarrierManager::Reset()
{
	for (int i = 0; i < 3; i++)
	{
		Barriers[i]->Reset();
	}
}
