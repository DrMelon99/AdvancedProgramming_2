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

		for (int i = 0; i < n_item; i++)
		{
			// getable 여부에 따른 아이템 시각화
			if (item[i].getable == true)
			{
				back_buf[item[i].ix][item[i].iy] = 'I';
			}
			else if (back_buf[item[i].ix][item[i].iy] == 'I')
			{
				back_buf[item[i].ix][item[i].iy] = ' ';
			}
		}

		for (int i  = 0; i < n_player; i++)
		{
			player_stamina(i, -1, -1);

			// 플레이어 인접 칸 아이템 탐색 (상.하.좌.우) (대각선 포함 X)
			for (int j = 0; j < n_item; j++)
			{
				if ((tick[0] - player[i].interact_timestamp > 1000) && (item[j].getable == true) &&
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
								if (item[k].id == player[i].item.id)
								{
									x = item[k].ix;
									y = item[k].iy;

;									item[k].ix = item[j].ix;
									item[k].iy = item[j].iy;

									item[j].ix = x;
									item[j].iy = y;

									item[k].getable = true;
								}
							}

							player[i].item = item[j];
							item[j].getable = false;
							player[i].interact_timestamp = tick[0];
							player_stamina(i, 1, player[i].item.stamina_buf);
						}
						else // 아이템 무시
						{
							player[i].interact_timestamp = tick[0];
						}
					}
					else // 플레이어가 아이템을 가지고 있지 않다면
					{
						player[i].item = item[j];
						item[j].getable = false;
						player[i].hasitem = true;
						player[i].interact_timestamp = tick[0];
						player_stamina(i, 1, player[i].item.stamina_buf);
					}
					debug_k++;
				}
			}

			// 플레이어 인접 칸 아이템 탐색 (상.하.좌.우) (대각선 포함 X)
			/*for (int j = i + 1; j < n_player; j++)
			{
				if ((player[j].is_alive == true) &&
					((((player[i].px + 1) == (player[j].px)) && ((player[i].py + 0) == (player[j].py))) ||
					(((player[i].px + 0) == (player[j].px)) && ((player[i].py + 1) == (player[j].py))) ||
					(((player[i].px - 1) == (player[j].px)) && ((player[i].py + 0) == (player[j].py))) ||
					(((player[i].px + 0) == (player[j].px)) && ((player[i].py - 1) == (player[j].py)))))
				{
					if (i == 0)
					{
						dialog(3);
					}
					else
					{
						fight[0] = randint(0, 2);
					}

					if ((player[i].hasitem == false) && (player[j].hasitem == true))
					{
						if((player[i].intel+player[i].item.intel_buf))
						if (fight[0] == 0) // 강탈
						{
							if ()
						}
						else if (fight[0] == 1) // 회유
						{

						}
						else // 무시
						{

						}
					}
					else if ((player[i].hasitem == true) && (player[j].hasitem == false))
					{
						if (fight[0] == 0) // 강탈
						{
							if ()
						}
						else if (fight[0] == 1) // 회유
						{

						}
						else // 무시
						{

						}
					}
					else if ((player[i].hasitem == true) && (player[j].hasitem == true))
					{
						if (fight[0] == 0) // 강탈 (교환)
						{
							if ()
						}
						else if (fight[0] == 1) // 회유 (교환)
						{

						}
						else // 무시
						{

						}
					}
				}
			}*/
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

	for (int i = 0; i < n_player; i++)
	{

	}

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
		player[j].period = randint(100, 200);

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
	}

	tick[0] = 0;
}