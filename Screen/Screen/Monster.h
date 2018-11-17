#ifndef MONSTER_H_
#define MONSTER_H_

#include "GameObject.h"
#include "Items.h"

class Monster : public GameObject
{
	Items& items;
	unsigned int n_absorbedItem;
public:
	Monster(Position pos = { 50,0 }, const string& shape = "&")
        : n_absorbedItem(0),items(Items::getInstance()),GameObject(pos, shape)
    {
    }

    void update()
    {
      move(rand() % 3 - 1, rand() % 3 - 1);
	  n_absorbedItem += items.absorbed(*this);
    }
	int getAbsorbedItem() 
	{ 
		return n_absorbedItem; 
	}
};


#endif

