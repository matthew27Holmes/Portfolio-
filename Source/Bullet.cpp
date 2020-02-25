#include "Bullet.h"
#include <Engine/Sprite.h>
#include <Engine/Input.h>
#include <Engine/Keys.h>

Bullet::Bullet(std::shared_ptr<ASGE::Renderer> renderer)
	:Actor(renderer)
{
	Pos = { 10,600 };
	speed = 20;
	Size = { 3,12 };
	setTag(ObjTags::Bull);
	if (!LoadSprite("..\\..\\Resources\\Textures\\TankBullet.jpg"))
	{
		std::cout << "error loading bullet";
		return;
	}
	alive = false;
}

void Bullet::handleCollisons(ObjTags tag)
{
	if ( tag == ObjTags::Barr || (Tag == ObjTags::EmyBull && (tag == ObjTags::Ply))
		|| (Tag == ObjTags::Bull && (tag == ObjTags::Emy)) )
	{
		killBullet();
	}
}

void Bullet::shoot(Vector2 pos, Vector2 offset)
{
	alive = true;
	//hitTarget = false;
	Pos = pos + offset;
}

void Bullet::MoveBullet(float velocity, float deltaTime)
{
	Pos.y += (velocity* speed)  * deltaTime;
}

void Bullet::killBullet()
{
	//turn off this bullet 
	//let parent no its gone 
	killSprite();
}

void Bullet::Reset()
{
	alive = false;
	Pos = { 10,600 };
}
