#pragma once
#include "Actor.h"
#include "Bullet.h"

class Player : public Actor
{
public:

	Player(std::shared_ptr<ASGE::Renderer> renderer);
	//Player(Player&&rhs);

	void Tick(float dt)override;
	void Render(std::shared_ptr<ASGE::Renderer> renderer) override;
	void handleCollisons(ObjTags tag) override;
	void addToObjList(std::vector<Actor*>&obj)override;

	void MoveHorizontally(float dt, float velocity) override;

	void Shoot();

	int playerHit();
	bool getIsAlive();
	void reset(bool PlayerWon);
private:
	//bool hasShot = false;	// when hits something becomes false
	int lives;
	Vector2 Thrust;
	Vector2 drag;
	//std::unique_ptr<Bullet> bullet;// should use object pool
	int bulletPoolSize = 30;
	std::unique_ptr<Bullet> bulletPool[30];
	std::vector<std::unique_ptr<ASGE::Sprite>> LivesCounter;
};