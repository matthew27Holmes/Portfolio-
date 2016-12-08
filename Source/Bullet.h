#pragma once
#include "Player.h"
class Bullet : public Player
{
public:
	float GetBulletY();
	float GetBulletX();
	float GetWidth();
	float Gethight();
	virtual void Render(std::shared_ptr<ASGE::Renderer> renderer);

	bool shoot(std::shared_ptr<ASGE::Renderer> renderer,float xops);
	void MoveBullet();
	bool getBulletFierd();
	void setBulletFierd(bool hasBulletBeenFierd);
	bool deleteBullet();
private:
	float Xpos;
	float Ypos;
	float Width;
	float Height;

	bool bulletFired;
	std::unique_ptr<ASGE::Sprite> Bullets;

};