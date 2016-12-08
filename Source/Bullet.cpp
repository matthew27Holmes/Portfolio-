#include "Bullet.h"
#include <Engine/Sprite.h>
#include <Engine/Input.h>
#include <Engine/Keys.h>

bool Bullet::shoot(std::shared_ptr<ASGE::Renderer> renderer,float xops)
{
	Bullets = renderer->createSprite();
	Bullets->position[0] = xops+23.5;
	Bullets->position[1] = 600;
	if (!Bullets->loadTexture("..\\..\\Resources\\Textures\\TankBullet.jpg"))
	{
		return false;
	}
	bulletFired = false;
}
bool Bullet::getBulletFierd()
{
	return bulletFired;
}
void Bullet::setBulletFierd(bool hasBulletBeenFierd)
{
	bulletFired = hasBulletBeenFierd;
}
void Bullet::MoveBullet()
{
	Bullets->position[1] = GetBulletY() - 5;
}
bool Bullet::deleteBullet()
{
	if (Bullets->position[1] == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
float Bullet::GetWidth()
{
	Width = Bullets->size[0];
	return Width;
}
float Bullet::Gethight()
{
	Height = Bullets->size[1];
	return Height;
}
float Bullet::GetBulletY()
{
	Ypos = Bullets->position[1];
	return Ypos;
}
float Bullet::GetBulletX()
{
	Xpos = Bullets->position[0];
	return Xpos;
}

void Bullet::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	Bullets->render(renderer);
}