#pragma once
#include "Actor.h"
class Barrier : public Actor
{
public:
	Barrier(Vector2 pos, Vector2 size, std::shared_ptr<ASGE::Renderer> renderer);
	void handleCollisons(ObjTags tag) override;

	void TakeDamge();
	int getHealth();
	void Reset();

private:
	int health;
};