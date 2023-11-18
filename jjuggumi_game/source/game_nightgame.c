#include "games.h"

void nightgame(void)
{
	nightgame_init();

	display();

	while (1)
	{
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT)
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++)
		{
			if (tick % player[i].period == 0)
			{
				move_random(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}

void nightgame_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	int x, y;
	for (int i = 0; i < n_player; i++)
	{
		// ���� �ڸ��� ������ �ٽ� ����
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		player[i].px = x;
		player[i].py = y;
		player[i].period = randint(100, 500);

		back_buf[player[i].px][player[i].py] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}