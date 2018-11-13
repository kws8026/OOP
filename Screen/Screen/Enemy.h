#ifndef ENEMY_H_
#define ENEMY_H_

#include "Players.h"
#include "Bullet.h"


class Enemy : public GameObject, public Damageable {
	float		hp;
	string		face;
	string		faceAttacked;
	int			nAnimations;
	Players&	players;
	float		speed = 2.0f / 30;

public:
	Enemy(Players& players, Position pos = {50,0}, int hp = 5, const string& face = "(*_*)")
		: GameObject(pos, face), Damageable(1.0f), players(players), nAnimations(0), hp(hp), face(face), faceAttacked("(>_<)")
	{}

	void update()
	{
		auto main = players.getMainCharacter();
		if (!main) return;
		Position player_pos = main->getPosition();
        Position pos = getPosition();
		if (player_pos.x < pos.x) move(-1 * speed);
		else if (player_pos.x > pos.x) move(1 * speed);
		else {} // do not move

		players.getDamagedIfAttacked(*this);		

		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			setShape(face);
		}
	}

	bool getDamagedIfAttacked(const GameObject& attacker)
	{
		auto bullet = dynamic_cast<const Bullet *>(&attacker); // it only gets attacked when bullets attack.
		if (!bullet) return false;
		Direction bullet_direction = bullet->getDirection();
        Position bullet_pos = bullet->getPosition();
        Position pos = getPosition();
		if ((bullet_direction == Direction::Left && pos.x < bullet_pos.x && bullet_pos.x - pos.x <= 1)
			|| (bullet_direction == Direction::Right && bullet_pos.x < pos.x && pos.x - bullet_pos.x <= 1)
			|| pos.x == bullet_pos.x) {
			hp -= getDamage();
			nAnimations = 30;
			setShape(faceAttacked);
			return true;
		}
		return false;
	}

	bool isAlive() {
		return hp > 0.0f;
	}

	float getHP() { return hp; }
};

#endif
