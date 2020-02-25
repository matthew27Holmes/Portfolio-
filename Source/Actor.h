#pragma once
#include "GameObject.h"
#include "Constants.h"


class Actor : public GameObject
{
public:
	Actor(std::shared_ptr<ASGE::Renderer> renderer);

	virtual void addToObjList(std::vector<Actor*>& obj);
	bool LoadSprite(char* spriteName);
	virtual void Render(std::shared_ptr<ASGE::Renderer> renderer);
	~Actor() = default;
	virtual void Tick(float dt);
	virtual void handleCollisons(ObjTags tag) { return; };


	bool hasSpriteHitRightWall();
	bool hasSpriteHitLeftWall();
	virtual void MoveHorizontally(float dt,float velocity);

	int getSpeed() { return speed; };
	void setSpeed(int sp) { speed = sp; };

	void killSprite();
protected:
	int speed;
	std::unique_ptr<ASGE::Sprite> Sprite;

};

