//#include"EnemyBullet .h"
//#include <Engine/Sprite.h>
//#include <Engine/Input.h>
//#include <Engine/Keys.h>
//
//bool EnemyBullet::shoot(std::shared_ptr<ASGE::Renderer> renderer,float xops, float ypos)
//{
//	EBullet = renderer->createSprite();
//	EBullet->position[0] = xops;//+23.5;
//	EBullet->position[1] = ypos;
//	if (!EBullet->loadTexture("..\\..\\Resources\\Textures\\TankBullet.jpg"))
//	{
//		return false;
//	}
//	//bulletFired = false;
//}
//void EnemyBullet::MoveBullet()
//{
//	EBullet->position[1] = GetEnemyBulletY() + 5;
//}
//
//bool EnemyBullet::getBulletFierd()
//{
//	return Fired;
//}
//void EnemyBullet::setBulletFierd(bool hasBulletBeenFierd)
//{
//	Fired = hasBulletBeenFierd;
//}
//
//bool EnemyBullet::deleteBullet()
//{
//	if (EBullet->position[1] == 590)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
//float EnemyBullet::GetWidth()
//{
//	Width = EBullet->size[0];
//	return Width;
//}
//float EnemyBullet::Gethight()
//{
//	Height = EBullet->size[1];
//	return Height;
//}
//float EnemyBullet::GetEnemyBulletY()
//{
//	Ypos = EBullet->position[1];
//	return Ypos;
//}
//float EnemyBullet::GetEnemyBulletX()
//{
//	Xpos = EBullet->position[0];
//	return Xpos;
//}
//void EnemyBullet::Render(std::shared_ptr<ASGE::Renderer> renderer)
//{
//		EBullet->render(renderer);
//}