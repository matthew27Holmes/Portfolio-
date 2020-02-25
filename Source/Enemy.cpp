#include"Enemy.h"
#include <Engine/Input.h>
#include <Engine/Keys.h>

Enemy::Enemy(int val,bool canFire,Vector2 pos, std::shared_ptr<ASGE::Renderer> renderer)
	: Actor(renderer), EnemeyFired(false),value(val),canEnemyFire(canFire)
{
	speed = 5;
	Pos = pos;
	Size = { 50,50 };
	setTag(ObjTags::Emy);
	enemybulletPt = std::make_unique<Bullet>(renderer);
	enemybulletPt->setTag(ObjTags::EmyBull);
}

void Enemy::addToObjList(std::vector<Actor*>&obj)
{
	obj.emplace_back(this);
	enemybulletPt->addToObjList(obj);
}

void Enemy::Tick(float dt)
{
	Actor::Tick(dt);
	if (EnemeyFired)// should move fire control to indiviual eneimes as oppsed to controler 
	{
		enemybulletPt->Tick(dt);// when enemy dies bullets tick stops being called 
		enemybulletPt->MoveBullet(1, dt);
		if (enemybulletPt->getPos().y >= WINDOW_HEIGHT)//out of bounds 
		{
			enemybulletPt->setAlive(false);
		}

		if (!enemybulletPt->getAlive())
		{
			EnemeyFired = false;
		}
	}
	else if(canEnemyFire && alive)
	{
		enemyFire();
	}
}

void Enemy::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	Actor::Render(renderer);
	if (EnemeyFired)
	{
		enemybulletPt->Render(renderer);
	}
}

void Enemy::handleCollisons(ObjTags tag)
{
	if (tag == Bull)
	{
		killSprite();
	}
}

void Enemy::enemyFire()// should only fire if you are at the front 
{
	int ran = rand() % 55 + 0;
	float spawnNumber = (float)rand() / (float)RAND_MAX;
	if (spawnNumber < 0.001)
	{
		enemybulletPt->shoot(Pos, { 0,0 });
		EnemeyFired = true;
	}
}

void Enemy::setCanFire(bool canFire)
{
	canEnemyFire = canFire;
}

int Enemy::Getvalue()
{
	return value;
}

void Enemy::reset(Vector2 pos, bool fireEnabled)
{
	Pos = pos;
	canEnemyFire = fireEnabled;
	enemybulletPt->Reset();
	alive = true;
}

