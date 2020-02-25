#include"Player.h"
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

//Player::Player(Player&&rhs)
//{
//	LivesCounter.reserve(10);
//	for (int i = 0; i < LivesCounter.size(); i++)
//	{
//		LivesCounter.push_back(std::move(Sprite));
//	}
//}

Player::Player(std::shared_ptr<ASGE::Renderer> renderer) 
	: Actor(renderer) , lives(3) //,bullet(std::make_unique<Bullet>(renderer))
{
	speed = 200;
	Pos = { WINDOW_WIDTH/2,WINDOW_HEIGHT - 200 };
	Size = { 50,50 };
	LoadSprite("..\\..\\Resources\\Textures\\Space-invadersShip.jpg");
	setTag(ObjTags::Ply);

	//set up lives counter 
	LivesCounter.resize(lives);
	int x = WINDOW_WIDTH / 10;
	for (int i = 0; i < (int)LivesCounter.size(); i++)
	{
		LivesCounter[i] = renderer->createSprite();
		LivesCounter[i]->position[0] = (float)x;
		LivesCounter[i]->position[1] = WINDOW_HEIGHT - 150.0f;
		x += 90;
		if (!LivesCounter[i]->loadTexture("..\\..\\Resources\\Textures\\Space-invadersShip.jpg"))
		{
			std::cout << "failed to load Lives counter Texture";
			return;
		}
		LivesCounter[i]->size[0] = 50;
		LivesCounter[i]->size[1] = 50;
	}

	//set up bullet pool 
	for (int i = 0; i < bulletPoolSize; i++)
	{
		bulletPool[i] = std::make_unique<Bullet>(renderer);
	}
}

void Player::addToObjList(std::vector<Actor*>&obj)
{
	obj.emplace_back(this);
	for (int i = 0; i < bulletPoolSize; i++)
	{
		bulletPool[i]->addToObjList(obj);
	}
}

void Player::Tick(float dt)
{
	Player::Actor::Tick(dt);
	for (int i = 0; i < bulletPoolSize; i++)
	{
		if (bulletPool[i]->getAlive())
		{
			bulletPool[i]->Tick(dt);
			bulletPool[i]->MoveBullet(-1, dt);
			if (bulletPool[i]->getPos().y <= 0)
			{
 				bulletPool[i]->setAlive(false);
			}
		}
	}
}

void Player::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	//bullet
	for (int i = 0; i < bulletPoolSize; i++)
	{
		if (bulletPool[i]->getAlive())
		{
			bulletPool[i]->Render(renderer);
		}
	}

	//lives 
	for (int i = 0; i < lives; i++)
	{
		//if (alive)
		//{
			LivesCounter[i]->render(renderer);
		//}
		//else
		//{
			//alive = true;
		//}
	}
	// render self 
	Actor::Render(renderer);
}

void Player::handleCollisons(ObjTags tag)
{
	if (tag == ObjTags::EmyBull)
	{
		playerHit();
	}
}

void Player::MoveHorizontally(float dt, float velocity)
{
	if ((velocity > 0 && !hasSpriteHitRightWall()) || (velocity < 0 && !hasSpriteHitLeftWall()))
	{
		Actor::MoveHorizontally(dt, velocity);
	}
}

void Player::Shoot()
{
	//search list for deactive bullet 
	//fire first deactive bullet 
	for (int i = 0; i < bulletPoolSize; i++)
	{
		if (!bulletPool[i]->getAlive())
		{
			bulletPool[i]->shoot(Pos, { 23.5f,0.0f });
			// set timer between bullets
			return;
		}
	}
	// if no bullets deactive // kill first bullet 
	bulletPool[0]->killBullet();
	bulletPool[0]->shoot(Pos, { 23.5f,0.0f });
	// set timer between bullets
}

int Player::playerHit()
{
	lives--;
	//reset postion 
	Pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT - 200 };
	if (lives <= 0)
	{
		alive = false;
	}
	//reset postion 
	Pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT - 200 };
	return lives;
}
bool Player::getIsAlive()
{
	return alive;
}

void Player::reset(bool PlayerWon)
{
	if (!PlayerWon)
	{
		lives = 3;
	}
	Pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT - 200 };

	//set up bullet pool 
	for (int i = 0; i < bulletPoolSize; i++)
	{
		bulletPool[i]->Reset();
	}

	alive = true;
}
