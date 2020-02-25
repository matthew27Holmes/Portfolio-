#pragma once
#include"Actor.h"

class Bullet : public Actor
{
public:
	Bullet(std::shared_ptr<ASGE::Renderer> renderer);
	void handleCollisons(ObjTags tag) override;

	void shoot(Vector2 pos, Vector2 offset);
	void MoveBullet(float velocity,float delatTime);
	void killBullet();
	void Reset();
};