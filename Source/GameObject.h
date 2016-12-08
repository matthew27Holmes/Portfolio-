#pragma once
#include "Game.h"
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>
#include <string>
#include<vector>
class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	/*float GetXpostion(int i);
	float GetYpostion(int i);
	float GetWidth(int i);
	float Gethight(int i);*/

	bool IsAlive();

private:
	int Health;
	/*float Xpos;
	float Ypos;
	float Width;
	float Height;*/
};