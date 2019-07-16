#pragma once
#include "Actor.h"
class Player : public Actor
{
public:
	Player();
	Player(Player&&rhs);
	virtual bool init(std::shared_ptr<ASGE::Renderer> renderer);

	void Render(std::shared_ptr<ASGE::Renderer> renderer);
	void moveLeft(float dt);
	void moveRight(float dt);
	virtual float GetXpostion(int i);
	virtual float GetYpostion(int i);
	float GetWidth(int i);
	float Gethight(int i);
	bool GetHasShot();
	bool SetHasShot(bool i);
	int playerHit();
	bool GetDeadSprites(int i);
	bool getIsAlive();
	void reset();
private:
	bool hasShot = false;	// when hits something becomes false
	bool isAlive;
	int speed;

	int lives;
	float Xpos;
	float Ypos;
	float Width;
	float Height;
	

	std::unique_ptr<ASGE::Sprite> player;
	std::vector<std::unique_ptr<ASGE::Sprite>>Tank;
	std::unique_ptr<ASGE::Sprite>DeadTankSprite;
	std::vector<bool>deadTanks;
};