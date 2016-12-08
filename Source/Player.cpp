#include"Player.h"
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

Player::Player(Player&&rhs)
{
	Tank.reserve(10);
	for (int i = 0; i < Tank.size(); i++)
	{
		Tank.push_back(std::move(player));
	}

}
Player::Player()
{
	deadTanks.resize(4);
	speed = 5;
	lives = 3;
	isAlive = true;
}
bool Player::init(std::shared_ptr<ASGE::Renderer> renderer)
{
	Tank.resize(4);
	int x = 100;
	
	for (int i = 0; i < Tank.size(); i++)
	{
		Tank[i] = renderer->createSprite();
		if (i == 0)
		{
			Tank[0]->position[0] = 500;
			Tank[0]->position[1] = 600;
		}
		else
		{
			Tank[i]->position[0] = x;
			Tank[i]->position[1] = 650;
			x += 90;
		}
		if (!Tank[i]->loadTexture("..\\..\\Resources\\Textures\\Space-invadersShip.jpg"))
		{
			return false;
		}

		Tank[i]->size[0] = 50;
		Tank[i]->size[1] = 50;
	}
	DeadTankSprite = renderer->createSprite();
	DeadTankSprite->position[0] = GetXpostion(0);
	DeadTankSprite->position[1] = GetYpostion(0);
	return true;
}

void Player:: moveLeft()
{
	if (!hasSpriteHitLeftWall(0,Tank))
	{
		MoveLeft(0,Tank ,speed);
	}
}
void Player::moveRight()
{
	if (!hasSpriteHitRightWall(0,Tank))
	{
		MoveRight(0,Tank ,speed);
	}
}
bool Player::GetHasShot()
{
	return hasShot;
}

bool Player::SetHasShot(bool i)
{
	hasShot = i;
	return hasShot;
}
void Player::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i = 0; i < 4; i++)
	{
		if (isAlive)
		{
			if (!deadTanks[i])
			{
				Tank[i]->render(renderer);
			}
		}
		else
		{
			DeadTankSprite->render(renderer);
			isAlive = true;
		}
	}
}

float Player::GetXpostion(int i)
{
	Xpos = Tank[i]->position[0];
	return Xpos;
}
float Player::GetYpostion(int i)
{
	Ypos = Tank[i]->position[1];
	return Ypos;
}
float Player::GetWidth(int i)
{
	Width = Tank[i]->size[0];
	return Width;
}
float Player::Gethight(int i)
{
	Height = Tank[i]->size[1];
	return Height;
}
int Player::playerHit()
{
	lives--;
	deadTanks[lives+1] = true;
	isAlive = false;
	return lives;
}
bool Player::getIsAlive()
{
	return isAlive;
}
bool Player::GetDeadSprites(int i)
{
	return deadTanks[i];
}
void Player::reset()
{
	lives = 3;
	isAlive = true;
	for (int i = 0; i < deadTanks.size(); i++)
	{
		deadTanks[i] = false;
	}
}
