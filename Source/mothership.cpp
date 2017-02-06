#include "mothership.h"
#include <Engine/Sprite.h>
#include <Engine/Input.h>
#include <Engine/Keys.h>

MotherShip::MotherShip()
{
	setRandomSide();
}
bool MotherShip::setRandomSide()
{
	float spawnNumber = (float)rand() / (float)RAND_MAX;
	if (spawnNumber < 0.5)
	{
		movingRight = true;
		Xpos = -100;
		return true;
	}
	else
	{
		movingRight = false;
		Xpos = WINDOW_WIDTH;
		return true;
	}
	/*else
	{
		return false;
	}*/
}
bool MotherShip::init(std::shared_ptr<ASGE::Renderer> renderer)
{
	Mship = renderer->createSprite();
	Mship->position[0] = Xpos;
	Mship->position[1] = 30;
	if (!Mship->loadTexture("..\\..\\Resources\\Textures\\spaceInvadersBouns.jpg"))
	{
		return false;
	}
	Spawnded = false;
}
bool MotherShip::getSpawnded()
{
	return Spawnded;
}
void MotherShip::setSpawnded(bool hasbeenSpawnded)
{
	Spawnded = hasbeenSpawnded;
}
bool MotherShip::hasHitWall()
{
	if (Mship->position[0] == -100)
	{
		return true;
	}
	else if(Mship->position[0] == WINDOW_WIDTH)
	{
		return false;
	}
}
void MotherShip::MoveShip()
{
	if (hasHitWall())
	{
		movingRight = true;
	}
	else if (!hasHitWall())
	{
		movingRight = false;
	}
	if (movingRight)
	{
		Mship->position[0] += 5;
	}
	if (!movingRight)
	{
		Mship->position[0] -= 5;
	}
	
}
bool MotherShip::deleteMotherShip()
{
	if (Mship->position[0] == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


void MotherShip::Render(std::shared_ptr<ASGE::Renderer> renderer)
{
	Mship->render(renderer);
}
float MotherShip::GetshipX()
{
	Xpos=Mship->position[0];
	return Xpos;
}
float MotherShip::GetshipY()
{
	Ypos = Mship->position[1];
	return Xpos;
}
float MotherShip::GetWidth()
{
	Width = Mship->size[0];
	return Xpos;
}
float MotherShip::Gethight()
{
	Height = Mship->size[1];
	return Xpos;
}