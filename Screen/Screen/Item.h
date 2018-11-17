#ifndef ITEM_H_
#define ITEM_H_

#include "GameObject.h"

class Item :
	public GameObject
{
	bool toggle;
public:
	Item(Position pos = { 50,0 },const string& shape = "@")
		: GameObject(pos, shape), toggle(true)
	{
	}
	void update()
	{
	}

	bool absorbed(const GameObject& target)
	{
		if (getPosition().x != target.getPosition().x||
			getPosition().y != target.getPosition().y) return false;
		toggle = false;
		return true;
	}
	bool isAlive(){
		return toggle;
	}
};

#endif