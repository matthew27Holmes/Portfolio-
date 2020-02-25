#pragma once
#include "Game.h"
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>
#include <string>
#include<vector>

/*i should extend this class to carry more generic functionaility 
like Tick functions,Handle collisons,kill object, rendering and handling object sprite
or have another class to handle sprite objects*/

class GameObject
{

public:
	GameObject() = default;
	~GameObject() = default;
	bool getAlive() { return alive; };
	virtual void setAlive(bool alive) { alive = alive; }

	virtual Vector2 getPos() { return Pos; }
	virtual void setPos(Vector2 pos) { Pos = pos; }

	virtual Vector2 getSize() { return Size; }	
	virtual void setSize(Vector2 size) { Size = size; }

	void setTag(ObjTags tag) { Tag = tag; };
	ObjTags getTag() { return Tag; };

	GameObject* getSelf() { return self; }

protected:
	//int Health;
	bool alive;
	Vector2 Pos;
	Vector2 Size;
	ObjTags Tag;
private:
	GameObject* self = this;
};