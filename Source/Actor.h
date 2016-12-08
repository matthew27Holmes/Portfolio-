#pragma once
#include "GameObject.h"
#include "Constants.h"


class Actor: 
	public GameObject
{
public:
	Actor()=default;
	~Actor()=default;
	
	bool hasSpriteHitRightWall(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite);
	bool hasSpriteHitLeftWall(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite);
	void MoveRight(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite, int speed);
	void MoveLeft(int i, std::vector<std::unique_ptr<ASGE::Sprite>>& ActorSprite, int speed);

	/*void killSprite(int i, std::unique_ptr<ASGE::Sprite> ActorSprite[55]);*/
	//virtual float GetXpostion(int i);
	//virtual float GetYpostion(int i);
private:
	int speed;
};

