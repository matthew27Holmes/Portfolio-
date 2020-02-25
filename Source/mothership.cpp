//#include "mothership.h"
//#include <Engine/Sprite.h>
//#include <Engine/Input.h>
//#include <Engine/Keys.h>
//
//MotherShip::MotherShip(int i, Vector2 pos,std::shared_ptr<ASGE::Renderer> renderer):Enemy(i,pos,renderer)
//{
//	setTag(ObjTags::Mother);
//	setRandomSide();
//}
//bool MotherShip::setRandomSide()
//{
//	float spawnNumber = (float)rand() / (float)RAND_MAX;
//	if (spawnNumber < 0.5)
//	{
//		movingRight = true;
//		Xpos = -110;
//		return true;
//	}
//	else
//	{
//		movingRight = false;
//		Xpos = WINDOW_WIDTH +10;
//		return true;
//	}
//
//}
//bool MotherShip::init(std::shared_ptr<ASGE::Renderer> renderer)
//{
//	Mship = renderer->createSprite();
//	Mship->position[0] = Xpos;
//	Mship->position[1] = 30;
//	if (!Mship->loadTexture("..\\..\\Resources\\Textures\\spaceInvadersBouns.jpg"))
//	{
//		return false;
//	}
//	Spawnded = false;
//	return true;
//}
//bool MotherShip::getSpawnded()
//{
//	return Spawnded;
//}
//void MotherShip::setSpawnded(bool hasbeenSpawnded)
//{
//	Spawnded = hasbeenSpawnded;
//}
//bool MotherShip::hasHitWall()
//{
//	if (Mship->position[0] == -110)
//	{
//		return true;
//	}
//	else if(Mship->position[0] == WINDOW_WIDTH+10)
//	{
//		return true;
//	}
//	return false;
//}
//void MotherShip::MoveShip()
//{
//	if (hasHitWall())
//	{
//		movingRight = true;
//	}
//	else if (!hasHitWall())
//	{
//		movingRight = false;
//	}
//	if (movingRight)
//	{
//		Mship->position[0] += 2;
//	}
//	if (!movingRight)
//	{
//		Mship->position[0] -= 2;
//	}
//	
//}
//bool MotherShip::deleteMotherShip()
//{
//	if (Mship->position[0] == 0)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
//
//
//void MotherShip::Render(std::shared_ptr<ASGE::Renderer> renderer)
//{
//	Mship->render(renderer);
//}
//float MotherShip::GetshipX()
//{
//	Xpos=Mship->position[0];
//	return Xpos;
//}
//float MotherShip::GetshipY()
//{
//	Ypos = Mship->position[1];
//	return Xpos;
//}
//float MotherShip::GetWidth()
//{
//	Width = Mship->size[0];
//	return Xpos;
//}
//float MotherShip::Gethight()
//{
//	Height = Mship->size[1];
//	return Xpos;
//}