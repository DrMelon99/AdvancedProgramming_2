#include "games.h"

void nightgame(void)
{
	nightgame_init();

	display();

	// dialog(0); // ī��Ʈ �ٿ� ���̾�α�

	while (1)
	{
		// 0�� �÷��̾� ������ ����
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

		// �׿� �÷��̾� ������ ����
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
				// getable ���ο� ���� ������ �ð�ȭ
				if (item[j].getable == true)
				{
					back_buf[item[j].ix][item[j].iy] = 'I';
				}
				else if (back_buf[item[j].ix][item[j].iy] == 'I')
				{
					back_buf[item[j].ix][item[j].iy] = ' ';
				}

				// �÷��̾� ���� ĭ Ž�� (��.��.��.��) (�밢�� ���� X)
				if ((item[j].getable == true) &&
					((((player[i].px + 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py + 1) == (item[j].iy))) ||
					(((player[i].px - 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py - 1) == (item[j].iy)))))
				{
					if (player[i].hasitem == true) // �÷��̾ �������� ������ ������
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

									do // �������� ��ȯ �� �������� �������� ��ġ�� ������
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
						else // ������ ����
						{
							back_buf[item[j].ix][item[j].iy] = ' ';

							do // �������� ��ġ�� ������
							{
								x = randint(1, N_ROW - 2);
								y = randint(1, N_COL - 2);
							} while (!placable(x, y));

							item[j].ix = x;
							item[j].iy = y;
						}
					}
					else // �÷��̾ �������� ������ ���� �ʴٸ�
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
	system("mode con: cols=80 lines=50"); // ���� 40

	map_init(25, 80);

	for (int j = 0; j < n_player; j++) // �÷��̾� ��ġ
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

	for (int j = 0; j < n_item ; j++) // ������ ��ġ
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