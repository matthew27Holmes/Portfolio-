#pragma once
#include "Barrier.h"
#include "CollisionDetction.h"

class BarrierManager {
public:
	BarrierManager(std::shared_ptr<ASGE::Renderer> renderer);
	~BarrierManager() {};

	void Tick(float dt);
	virtual void Render(std::shared_ptr<ASGE::Renderer> renderer);
	void addToObjList(std::vector<Actor*>&obj);

	bool checkForCollions(GameObject* collidingObject, CollisionDetction* collPt);

	Barrier* getBarrier(int i);

	
	void Reset();

private:
	std::vector<std::unique_ptr<Barrier>>Barriers;

};