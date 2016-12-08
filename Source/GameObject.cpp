#include "GameObject.h"

bool GameObject::IsAlive()
{
	if (Health<= 0)
	{
		return false;
	}
	return true;
}

//float GameObject::GetXpostion(int i)
//{
//	return Xpos;
//}
//float GameObject::GetYpostion(int i)
//{
//	return Ypos;
//}
//float GameObject::GetWidth(int i)
//{
//
//	return Width;
//}
//float GameObject::Gethight(int i)
//{
//
//	return Height;
//}