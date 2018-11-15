#pragma once
#ifndef  MONSTERS_H_
#define MONSTERS_H_

#include "Monster.h"
#include <algorithm>
#include <vector>

class Monsters {
    Renderer&			renderer;
    vector<Monster*>		container;

    int n_movetimes;
    const unsigned int max_Monsters;

public:
    Monsters()
        : renderer(Renderer::getInstance()), n_movetimes(0),max_Monsters(5)
    {
        container.push_back(new Monster( { rand() % renderer.getScreenLength(),0 }));
    }

    void update()
    {
        // update all Monsters
        for (auto Monster : container) Monster->update();
    }

    void draw()
    {
        for (auto Monster : container) Monster->draw();
        Borland::gotoxy(0, 26); printf("# of Monsters = %2d,  ", container.size());
        for (auto Monster : container) printf("%2.1f %2.1f  ", Monster->getPosition());
    }
};


#endif



