#pragma once
#include "Actor.h"
#include "Bullet.h"
class EnemyController;

class Enemy : public Actor
{
public:
	Enemy(int val, bool canFire, Vector2 pos, std::shared_ptr<ASGE::Renderer> renderer);
	//Enemy(Enemy&&rhs);

	void Tick(float dt) override;
	void Render(std::shared_ptr<ASGE::Renderer> renderer) override;
	void handleCollisons(ObjTags tag) override;
	void addToObjList(std::vector<Actor*>&obj) override;

	void enemyFire();
	void setCanFire(bool canFire);
	int Getvalue();
	void reset(Vector2 pos,bool fireEnabled);

private:
	std::unique_ptr<Bullet> enemybulletPt;

	bool EnemeyFired;
	bool canEnemyFire;
	int value;
};