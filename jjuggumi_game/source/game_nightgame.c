#include "games.h"

void nightgame(void)
{
	nightgame_init();

	display();

	dialog(0); // 카운트 다운 다이얼로그

	while (1)
	{
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT)
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			move_manual(key);
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++)
		{
			if (tick % player[i].period == 0)
			{
				move_random_nightgame(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}

	for (int i = 0; i < n_player; i++)
	{
		player[i].stamina += randint(40, 50);
	}
}

void nightgame_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=80 lines=40");

	map_init(25, 80);

	int x, y;

	for (int i = 0; i < n_player; i++) // 플레이어 배치
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		player[i].px = x;
		player[i].py = y;
		player[i].period = randint(100, 300);

		back_buf[player[i].px][player[i].py] = '0' + i;  // (0 .. n_player-1)
	}

	for (int i = 0; i < n_item ; i++) // 아이템 배치
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		item[i].ix = x;
		item[i].iy = y;
		back_buf[item[i].ix][item[i].iy] = 'I';
	}

	tick = 0;
}