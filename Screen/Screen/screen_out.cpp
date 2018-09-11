#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

void check_range(int* pos, int screen_size)
{
	if (*pos < 0) *pos = 0;
	if (*pos >= screen_size - 1) *pos = screen_size - 1;
}

int main()
{
	const int screen_size = 119;
	char screen[screen_size + 1 + 1];
	int player_pos = 20;
	int enemy_pos = 50;
	char player[100];
	char enemy[100];

	strcpy(player, "(^_^)");
	strcpy(enemy, "(*__*)");
	int bullet_pos = -1;

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
				player_pos--;
				break;
			case 'd': case 77:
				player_pos++;
				break;
			case 72:
				enemy_pos++;
				break;
			case 80:
				enemy_pos--;
				break;
			case ' ':
				bullet_pos = player_pos;
				break;
				
			}
		}
		check_range(&player_pos, screen_size);
		check_range(&enemy_pos, screen_size);
		strncpy(screen + player_pos, player, strlen(player));
		strncpy(screen + enemy_pos, enemy, strlen(enemy));
		if (bullet_pos >= 0 && bullet_pos <= screen_size) {
			screen[bullet_pos] = '-';
			
			if (player_pos < enemy_pos) bullet_pos++;
			else if (enemy_pos < player_pos) bullet_pos--;
			if (bullet_pos == enemy_pos) bullet_pos = -1;
		}

		screen[screen_size] = '\r';
		screen[screen_size + 1] = 0;
		printf("%s", screen);
		Sleep(66);
	}

	return 0;
}