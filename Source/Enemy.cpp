
#include"Enemy.h"
//#include "Actor.h"
#include <Engine/Input.h>
#include <Engine/Keys.h>

Enemy::Enemy(Enemy&&rhs)
{
	Enemys.reserve(55);
	for (int i = 0; i < Enemys.size(); i++)
	{
		Enemys.push_back(std::move(Invaders));
	}
	
}
Enemy::Enemy()
{
	Deadsprite.resize(55);
	MovingRight = true;
	speed = 1;
	howManyEnemiesKilled = 0;
}

bool Enemy::init(std::shared_ptr<ASGE::Renderer> renderer)
{
	Enemys.resize(55);
	

	float x = 120;
	float y = 80;
	for (auto& enemy : Enemys)
	{
	
		enemy = renderer->createSprite();
		enemy->position[0] = x;
		enemy->position[1] = y;
		x += 70;
		if (x == 890)
		{
			y += 70;
			x = 120;
		}
		if (!enemy->loadTexture("..\\..\\Resources\\Textures\\Invader.jpg"))
		{
			return false;
		}
	}
	return true;
}
float Enemy::GetXpostion(int i)
{
	Xpos = Enemys[i]->position[0];
	return Xpos;
}
float Enemy::GetYpostion(int i)
{
	Ypos = Enemys[i]->position[1];
	return Ypos;
}
float Enemy::GetWidth(int i)
{
	Width = Enemys[i]->size[0];
	return Width;
}
float Enemy::Gethight(int i)
{
	Height = Enemys[i]->size[1];
	return Height;
}
void Enemy::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i=0; i < 55; i++)
	{
		if (!Deadsprite[i])
		{
			Enemys[i]->render(renderer);
		}
	}
}

void Enemy::Move()
{
	for (int i = 0; i < 55; i++)
	{	
		
		if (hasSpriteHitLeftWall(i, Enemys))
		{
			MovingRight = true;
			MoveDown();
		}
		else if (hasSpriteHitRightWall(i, Enemys))
		{
			MovingRight = false;
			MoveDown();
		}
		if (MovingRight)
		{
			MoveRight(i, Enemys, speed);
		}
		if (!MovingRight)
		{
			MoveLeft(i,Enemys, speed);
		}
	}
}
void Enemy::MoveDown()
{
	for (int i = 0; i < 55; i++)
	{
		Enemys[i]->position[1] = GetYpostion(i) + 10;
	}
}

bool Enemy::hasEnemyhasWon()
{
	for (int i=0; i < 55; i++)
	{
		if (!Deadsprite[i])
		{
			if (Enemys[i]->position[1] >= 560)
			{
				HasEnemyWon = true;
			}
		}
	}
	return HasEnemyWon;
}
bool Enemy::getHasEnemyWon()
{
	return HasEnemyWon;
}
void Enemy::killSprite(int i)
{
	Deadsprite[i] = true;
	howManyEnemiesKilled++;	
}
bool Enemy::areAllSpritesDead()
{
	if (howManyEnemiesKilled == 55)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Enemy::GetDeadSprites(int i)
{
	return Deadsprite[i];
}
void Enemy::reset()
{
	for (int i = 0; i < Deadsprite.size(); i++)
	{
		Deadsprite[i] = false;
	}
	HasEnemyWon = false;
	howManyEnemiesKilled = 0;
	score= 0;
}
void Enemy::setEnemyWin(bool hasWon)
{
	HasEnemyWon = hasWon;
}