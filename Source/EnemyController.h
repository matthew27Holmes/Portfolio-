#pragma once
#include "Enemy.h"

class EnemyController
{
public:
	EnemyController(std::shared_ptr<ASGE::Renderer> renderer);
	~EnemyController();
	void Tick(float dt);
	void Render(std::shared_ptr<ASGE::Renderer> renderer);
	void reset();
	void addToObjList(std::vector<Actor*>&obj);

	Enemy* getEnemy(int x,int y);
	void Move(float dt,std::unique_ptr<Enemy>& enemy);
	void MoveDown(float dt);
	
	//void enemyDied(int x, int y);
	//void speedUp();
	//void FindDeadSprites();
	bool areAllSpritesDead();
	bool hasEnemyhasWon();
	bool getHasEnemyWon();
	void setEnemyWin(bool hasWon);
	int getScore() { return score; };

private:
	std::vector<std::vector<std::unique_ptr<Enemy>>> Enemies;
	std::vector<std::vector<bool>> deadEnemies;
	//std::unique_ptr<MotherShip> MotherShipPt;
	Vector2 EnemyGrid;
	int howManyEnemiesKilled;
	int score;
	float speed;
	float const maxSpeed = 50;
	bool MovingRight;
	bool HasEnemyWon;
};

