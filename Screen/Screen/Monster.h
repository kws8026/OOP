#ifndef MONSTER_H_
#define MONSTER_H_

#include "GameObject.h"

class Monster : public GameObject {
    string		face;
public:
    Monster(Position pos = { 50,0 }, int hp = 10, const string& face = "(*_*)")
        : GameObject(pos, face),face(face)
    {
    }

    void update()
    {
      move(rand() % 2 - 1, rand() % 2 - 1);
    }
};
#endif

