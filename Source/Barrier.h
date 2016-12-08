#pragma once
#include "GameObject.h"
class Barrier : public GameObject
{
public:
	Barrier();
	virtual bool init(std::shared_ptr<ASGE::Renderer> renderer);
	float GetBarrierY(int i);
	float GetBarrierX(int i);
	float GetWidth(int i);
	float Gethight(int i);
	virtual void Render(std::shared_ptr<ASGE::Renderer> renderer);
	void TakeDamge(int i);
	void deleteBarrier(int i);
	int getHealth(int i);
	void Reset();
private:
	float Xpos;
	float Ypos;
	float Width;
	float Height;
	std::vector<bool>deadBarriers;
	std::vector<int>health;
	std::unique_ptr<ASGE::Sprite> Barriers;
	std::vector<std::unique_ptr<ASGE::Sprite>>Blocks;


};