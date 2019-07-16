
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
	Enemys.resize(55);
	EnemyVal.resize(55);
	Deadsprite.resize(55);
	MovingRight = true;
	speed = 20;
	howManyEnemiesKilled = 0;
}

bool Enemy::init(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i = 0; i < 55; i++)
	{
	
		Enemys[i] = renderer->createSprite();
		Enemys[i]->position[0] = x;
		Enemys[i]->position[1] = y;
		if (Enemys[i]->position[1] == 80)
		{
			sprite = "..\\..\\Resources\\Textures\\spaceInvaders40.jpg";
			EnemyVal[i] = val;
		}
		else if (y == 150||y==220)
		{
			sprite = "..\\..\\Resources\\Textures\\spaceInvaders.PNG";
			EnemyVal[i] = val-10;
		}
		
		else if (y == 290 || y == 360)
		{
		  sprite = "..\\..\\Resources\\Textures\\spaceInvaders10.jpg";
		  EnemyVal[i] = val-20;
		}
		x += 70;
		if (x == 890)
		{
			y += 70;
			x = 120;
		}
		
		if (!Enemys[i]->loadTexture(sprite))
		{
			return false;
		}
	}
	HasEnemyWon = false;
	howManyEnemiesKilled = 0;
	score = 0;
	return true;
}

int Enemy::Getvalue(int i)
{
	return EnemyVal[i];
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

void Enemy::Move(float dt)
{
	for (int i = 0; i < 55; i++)
	{	
		
		if (hasSpriteHitLeftWall(i, Enemys))
		{
			MovingRight = true;
			MoveDown(dt);
		}
		else if (hasSpriteHitRightWall(i, Enemys))
		{
			MovingRight = false;
			MoveDown(dt);
		}
		if (MovingRight)
		{
			MoveRight(i, Enemys, speed,dt);
		}
		if (!MovingRight)
		{
			MoveLeft(i,Enemys, speed,dt);
		}
	}
}
void Enemy::MoveDown(float dt)
{
	for (int i = 0; i < 55; i++)
	{
		Enemys[i]->position[1] = GetYpostion(i) + 5;
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
	x = 120;
	y = 80;
}
void Enemy::setEnemyWin(bool hasWon)
{
	HasEnemyWon = hasWon;
}