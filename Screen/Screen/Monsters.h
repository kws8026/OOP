#pragma once
#ifndef  MONSTERS_H_
#define MONSTERS_H_

#include "Monster.h"
#include <algorithm>
#include <vector>

class Monsters : public SizedMove{
    Renderer&			renderer;
    vector<Monster*>	container;
	

    int n_movetimes;
    int n_move_cool_time;

    const unsigned int max_Monsters;

public:
	Monsters()
		: renderer(Renderer::getInstance()), n_move_cool_time(60), n_movetimes(0), max_Monsters(36)
	{
		Position screenSize = renderer.getScreenSize();
		while (container.size() != max_Monsters) 
			container.push_back(new Monster({ rand() % screenSize.x,rand() % screenSize.y }));
	}
	
    void update()
    {
        // update all Monsters
		if (n_move_cool_time == 60){
			for (auto Monster : container) {
				Monster->update();
				checkRange(*Monster);
			}
			n_movetimes++;
			n_move_cool_time = 0;
		}
		else
			n_move_cool_time++;
    }

    void draw()
    {
        for (auto Monster : container) Monster->draw();
        Borland::gotoxy(0, 21); printf("# of Monsters = %2d\n", (int)container.size());
        for (auto Monster : container) printf("(%3d,%2d)%2d", Monster->getPosition().x, Monster->getPosition().y, Monster->getAbsorbedItem());
		printf("\n# movetimes = %d", n_movetimes);
	}
	int getMovetimes() { return n_movetimes; }
};


#endif



