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
	bool IsAlive();
private:
	int Health;
};