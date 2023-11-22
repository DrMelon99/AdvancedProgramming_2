#include "games.h"

void nightgame(void)
{
	nightgame_init();

	display();

	// dialog(0); // 카운트 다운 다이얼로그

	while (1)
	{
		// 0번 플레이어 움직임 정의
		key_t key = get_key();
		if (key == K_QUIT)
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			if (key != K_SPACE)
			{
				move_manual(key);
				player[0].stamina--;
			}
		}

		// 그외 플레이어 움직임 정의
		for (int i = 1; i < n_player; i++)
		{
			if (tick[0] % player[i].period == 0)
			{
				move_random_nightgame(i, -1);
			}
		}

		for (int i  = 0; i < n_player; i++)
		{
			for (int j = 0; j < n_item; j++)
			{
				// getable 여부에 따른 아이템 시각화
				if (item[j].getable == true)
				{
					back_buf[item[j].ix][item[j].iy] = 'I';
				}
				else if (back_buf[item[j].ix][item[j].iy] == 'I')
				{
					back_buf[item[j].ix][item[j].iy] = ' ';
				}

				// 플레이어 인접 칸 탐색 (상.하.좌.우) (대각선 포함 X)
				if ((item[j].getable == true) &&
					((((player[i].px + 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py + 1) == (item[j].iy))) ||
					(((player[i].px - 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py - 1) == (item[j].iy)))))
				{
					if (player[i].hasitem == true) // 플레이어가 아이템을 가지고 있으면
					{
						if (i == 0)
						{
							dialog(2);
						}
						else
						{
							get_item = randint(0, 1);
						}

						if (get_item == true)
						{
							for (int k = 0; k < n_item; k++)
							{
								if (player[i].item.id == item[k].id)
								{
									item[k].getable = true;

									do // 아이템을 교환 후 내려놓은 아이템의 위치를 재조정
									{
										x = randint(1, N_ROW - 2);
										y = randint(1, N_COL - 2);
									} while (!placable(x, y));

									item[k].ix = x;
									item[k].iy = y;
								}
							}

							player[i].item = item[j];
							item[j].getable = false;

							player_stamina(i, 1);
						}
						else // 아이템 무시
						{
							back_buf[item[j].ix][item[j].iy] = ' ';

							do // 아이템의 위치를 재조정
							{
								x = randint(1, N_ROW - 2);
								y = randint(1, N_COL - 2);
							} while (!placable(x, y));

							item[j].ix = x;
							item[j].iy = y;
						}
					}
					else // 플레이어가 아이템을 가지고 있지 않다면
					{
						player[i].item = item[j];
						item[j].getable = false;
						player[i].hasitem = true;
						player_stamina(i, 1);
					}
					debug_k++;
				}
			}
		}
		display();
		Sleep(10);
		tick[0] += 10;
	}

	for (int i = 0; i < n_player; i++)
	{
		player[i].stamina += randint(40, 50);
		if (player[i].stamina > 100)
		{
			player[i].stamina = 100;
		}
	}
}

void nightgame_init(void)
{
	debug_i = debug_j = debug_k = 0;

	game_round = 2;

	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=80 lines=50"); // 원래 40

	map_init(25, 80);

	for (int j = 0; j < n_player; j++) // 플레이어 배치
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		player[j].px = x;
		player[j].py = y;
		player[j].period = randint(100, 300);

		back_buf[player[j].px][player[j].py] = '0' + j;  // (0 .. n_player-1)
	}

	for (int j = 0; j < n_item ; j++) // 아이템 배치
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		item[j].ix = x;
		item[j].iy = y;
		back_buf[item[j].ix][item[j].iy] = 'I';
	}

	tick[0] = 0;
}