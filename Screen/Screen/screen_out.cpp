#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

class Player {
	int pos = 20;
	char face[100] = "(-_-)";
public:
	void move(int inc) { pos += inc;  }

	int getPosition() const { return pos;  }
	void checkRange(int screen_size)
	{
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char* screen, int screen_size)
	{
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
};

class Enemy {
	int pos = 50;
	char face[100] = "(*_*)";
	char faceAttacked[100] = "(>__<)";
	int nAnimations = 0;
public:
	void move(int inc) { pos += inc; }
	int getPosition() const { return pos; }
	void checkRange(int screen_size)
	{
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char* screen, int screen_size)
	{
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
	void update()
	{
		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			strcpy(face, "(^_^)");
		}
	}
	void OnHit()
	{
		nAnimations= 30;
		strcpy(face, faceAttacked);
	}

};

class Bullet {
	int pos = -1;
	char shape = '-';
public:
	Bullet(int player_pos) : pos(player_pos) {}
	void move(int inc) { pos += inc; }
	int getPosition() { return pos; }
	void checkRange(int screen_size)
	{
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char* screen, int screen_size)
	{
		checkRange(screen_size);
		screen[pos] = shape;
	}

	void update(const Player* player, const Enemy* enemy)
	{
		if (!player || !enemy) return;
		if (player->getPosition() < enemy->getPosition())
		{
			move(1);
		}
		else {
			move(-1);
		}
	}
};


int main()
{
	const int screen_size = 119;
	char screen[screen_size + 1 + 1];
	Player player;
	Enemy enemy;
	Bullet* pBullet = nullptr;		

	while (true)
	{
		memset(screen, ' ', screen_size);

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'a': case 75:
				player.move(-1);
				break;
			case 'd': case 77:
				player.move(1);
				break;
			case 72:
				enemy.move(1);
				break;
			case 80:
				enemy.move(-1);
				break;
			case ' ':
				if (pBullet == nullptr) {
					pBullet = new Bullet(player.getPosition());
				}
				break;
			}				
		}
		player.draw(screen, screen_size);
		enemy.draw(screen, screen_size);
		if (pBullet != nullptr) {
			pBullet->draw(screen, screen_size);
			if (pBullet->getPosition() == enemy.getPosition())
			{
				enemy.OnHit();
				delete pBullet;
				pBullet = nullptr;
			}
			else {
				pBullet->update(&player, &enemy);
				
			}
		}
		enemy.update();

		screen[screen_size] = '\r';
		screen[screen_size + 1] = 0;
		printf("%s", screen);
		Sleep(66);
	}

	return 0;
}