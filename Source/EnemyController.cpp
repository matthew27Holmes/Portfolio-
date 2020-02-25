#include "EnemyController.h"

EnemyController::EnemyController(std::shared_ptr<ASGE::Renderer> renderer)
	:MovingRight(true),howManyEnemiesKilled(0),HasEnemyWon(false),score(0)
{
	speed = 5;
	EnemyGrid.x = 11;
	EnemyGrid.y = 5;
	Enemies.resize(EnemyGrid.x);
	deadEnemies.resize(EnemyGrid.x);

	for (int i = 0; i < EnemyGrid.x; i++)
	{
		Enemies[i].resize(EnemyGrid.y);
		deadEnemies[i].resize(EnemyGrid.y);
	}
	float x = WINDOW_WIDTH/10;//120;
	float y = WINDOW_HEIGHT/5;
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			Vector2 pos = { x,y };
			bool canUnitFire = false;

			if (h == 0)
			{
				Enemies[w][h] = std::make_unique<Enemy>(40, canUnitFire, pos, renderer);
				Enemies[w][h]->LoadSprite("..\\..\\Resources\\Textures\\spaceInvaders40.jpg");
			}
			else if (h == 1 || h == 2)
			{
				Enemies[w][h] = std::make_unique<Enemy>(30, canUnitFire, pos, renderer);
				Enemies[w][h]->LoadSprite("..\\..\\Resources\\Textures\\spaceInvaders.PNG");
			}
			else if (h == 3 || h == 4)
			{
				if (h == 4)
				{
					canUnitFire = true;
				}
				Enemies[w][h] = std::make_unique<Enemy>(20, canUnitFire, pos, renderer);
				Enemies[w][h]->LoadSprite("..\\..\\Resources\\Textures\\spaceInvaders10.jpg");
			}
			x += 70;
		}
		y += 70;
		x = WINDOW_WIDTH / 10;
	}
	//MotherShipPt = std::make_unique<MotherShip>(100, Vector2{ -110 ,30},renderer);
	//MotherShipPt->init(renderer);
}

EnemyController::~EnemyController()
{
}

Enemy* EnemyController::getEnemy(int x,int y)
{
	return Enemies[x][y].get();
}

void EnemyController::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			Enemies[w][h]->Render(renderer);
		}
	}
	//MotherShipPt->Render(renderer);
}

void EnemyController::Tick(float dt)
{
	if (!hasEnemyhasWon())
	{
		for (int h = 0; h < EnemyGrid.y; h++)
		{
			for (int w = 0; w < EnemyGrid.x; w++)
			{
				Enemies[w][h]->Tick(dt);
				Move(dt, Enemies[w][h]);
				Enemies[w][h]->setSpeed(speed);
				
				if (!Enemies[w][h]->getAlive() && !deadEnemies[w][h])// find dead sprites 
				{
					howManyEnemiesKilled++;
					deadEnemies[w][h] = true;
					score += Enemies[w][h]->Getvalue();
					speed = (speed*1.1f) < maxSpeed ? speed * 1.1f:maxSpeed;//if speed is less the max speed then incease else dont
					// allow the enemy behind to start firing 
					if (h > 0)
					{
						Enemies[w][h - 1]->setCanFire(true);
					}
				}
			}
		}
		//MotherShipPt->Tick(deltaTime);
		//MotherShipPt->MoveShip();
	}
}

void EnemyController::Move(float dt, std::unique_ptr<Enemy>& enemy)
{
		if (enemy->hasSpriteHitLeftWall())
		{
			MovingRight = true;
			MoveDown(dt);
		}
		else if (enemy->hasSpriteHitRightWall())
		{
			MovingRight = false;
			MoveDown(dt);
		}

		if (MovingRight)
		{
			enemy->MoveHorizontally(dt,1);
		}else
		{
			enemy->MoveHorizontally(dt,-1);
		}
}

void EnemyController::MoveDown(float dt)
{
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			Vector2 newPos = Enemies[w][h]->getPos();
			newPos.y += 5;
			Enemies[w][h]->setPos(newPos);
		}
	}
}

bool EnemyController::hasEnemyhasWon()
{
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			if (Enemies[w][h]->getAlive() && Enemies[w][h]->getPos().y>= WINDOW_HEIGHT/1.15)//-350//650
			{
				HasEnemyWon = true;
				return HasEnemyWon;
			}
		}
	}
	HasEnemyWon = false;
	return HasEnemyWon;
}

bool EnemyController::getHasEnemyWon()
{
	return HasEnemyWon;
}

bool EnemyController::areAllSpritesDead()
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

void EnemyController::reset()
{
	float x = WINDOW_WIDTH / 10;//120;
	float y = WINDOW_HEIGHT / 5;
	
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			Vector2 pos = { x,y };
			bool canUnitFire = h ==4 ?true: false;
			Enemies[w][h]->reset(pos,canUnitFire);
			deadEnemies[w][h] = false;
			x += 70;
		}
		y += 70;
		x = WINDOW_WIDTH / 10;
	}
	score = 0;
	speed = 5;
	MovingRight = false;
	howManyEnemiesKilled = 0;
	HasEnemyWon = false;
}

void EnemyController::addToObjList(std::vector<Actor*>& obj)
{
	for (int h = 0; h < EnemyGrid.y; h++)
	{
		for (int w = 0; w < EnemyGrid.x; w++)
		{
			Enemies[w][h]->addToObjList(obj);
		}
	}
}
void EnemyController::setEnemyWin(bool hasWon)
{
	HasEnemyWon = hasWon;
}