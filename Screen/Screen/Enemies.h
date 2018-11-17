#ifndef  ENEMIES_H_
#define ENEMIES_H_

#include "Enemy.h"
#include "Bullet.h"
#include "Players.h"
#include <algorithm>
#include <vector>

class Enemies {
	Renderer&			renderer;
	Players&			players;
	vector<Enemy*>		container;

	int n_killed;
	int n_remainings_for_respawn;
	const unsigned int max_enemies;

public:
	Enemies(Players& players)
		: renderer(Renderer::getInstance()), n_killed(0), n_remainings_for_respawn(30), players(players), max_enemies(5)
	{	container.push_back(new Enemy(players, {rand() % renderer.getScreenLength(),0 })); }

	int getNumberOfKilled() { return n_killed; }

	void update()
	{
		// spawn enemies periodically.
		if (n_remainings_for_respawn <= 0) {
			// reset the timer for the next enemy spawning
			if (container.size() < max_enemies)
				container.push_back(new Enemy(players, {rand() % renderer.getScreenLength(), 0
        }));
			n_remainings_for_respawn = 30;
		} else {
			n_remainings_for_respawn--;
		}

		// update all enemies
		for (auto enemy : container) enemy->update();
		
		int size = (int)container.size();
		container.erase(remove_if(container.begin(), container.end(), 
			[](Enemy* enemy) { 
				if (enemy->isAlive() == false) { 
					delete enemy; // you need to free the dynamically allocated enemies.
					return true;
				}
				return false; 
			}), container.end());
		n_killed += size - (int)container.size();
	}

	void draw()
	{
		for (auto enemy : container) enemy->draw();
		Borland::gotoxy(0, 2); printf("# of enemies = %2d,  ", (int)container.size());
		for (auto enemy : container) printf("%2d %2.1f  ", enemy->getPosition().x, enemy->getHP());
	}

	Enemy* findClosest(Position pos)
	{
		Enemy* closest = nullptr;
		float dist = 0.0f;
		if (renderer.checkRange(pos.x) == false) return closest;
		for (auto enemy : container) {
			Position enemy_pos = enemy->getPosition();
			if (renderer.checkRange(enemy_pos.x) == false) continue;
			float current_dist = fabs((float)pos.x - (float)enemy_pos.x);
			if (!closest) {
				dist = current_dist;
				closest = enemy;
				continue;
			}
			// closest != nullptr;
			if (dist > current_dist) {
				dist = current_dist;
				closest = enemy;
			}
		}
		return closest;
	}

	bool isShoted(Bullet& bullet)
	{
		auto enemy = findClosest(bullet.getPosition());
		if (!enemy) return false;
		return enemy->getDamagedIfAttacked(bullet);
	}
};


#endif

