#include "games.h"

void nightgame(void)
{
	nightgame_init();

	dialog(0, -1);

	while (1) // ���� ���� ����
	{
		// 'q'�� �����ų�, ���� �ο��� �Ѹ��� ���
		if (player_control() || (n_alive == 1))
			break;
		
		npc_move_nightgame();

		player_visable();

		nightgame_item_visable();

		if (tick[0] - tick[1] > 2000)
			print_addi_status(0, -1, -1);

		for (int i  = 0; i < n_player; i++)
		{
			// �÷��̾� ���� ĭ ������ Ž�� (��.��.��.��) (�밢�� ���� X)
			for (int j = 0; j < n_item; j++)
			{
				if ((tick[0] - player[i].interact_timestamp > 1000) && (item[j].getable == true) && player[i].is_alive[0] &&
					((((player[i].px + 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py + 1) == (item[j].iy))) ||
					(((player[i].px - 1) == (item[j].ix)) && ((player[i].py + 0) == (item[j].iy))) ||
					(((player[i].px + 0) == (item[j].ix)) && ((player[i].py - 1) == (item[j].iy)))))
				{
					if (player[i].hasitem == true) // �÷��̾ �������� ������ ������
					{
						if (i == 0)
						{
							dialog(2, -1);
						}
						else
						{
							get_item = randint(0, 1);
						}

						if (get_item == true) // ������ ��ȯ (������ ��ȯ �� ���� �������� �÷��̾� ���� �ݰ� 3ĭ ���� ���ġ -> �������� ������ ����?)
						{
							for (int k = 0; k < n_item; k++)
							{
								if (item[k].id == player[i].item.id)
								{
									do
									{
										x = randint(player[i].px - 3, player[i].px + 3);
										y = randint(player[i].py - 3, player[i].py + 3);
									} while (!placable(x, y));

									item[k].ix = x;
									item[k].iy = y;
									item[k].getable = true;
								}
							}

							player[i].item = item[j];
							item[j].getable = false;
							player[i].interact_timestamp = tick[1] = tick[0];
							print_addi_status(0, -1, -1);
							print_addi_status(3, i, -1);
							player_stamina(i, 1, player[i].item.stamina_buf);
						}
						else // ������ ����
						{
							player[i].interact_timestamp = tick[0];
						}
					}
					else // �÷��̾ �������� ������ ���� �ʴٸ�
					{
						player[i].item = item[j];
						item[j].getable = false;
						player[i].hasitem = true;
						player[i].interact_timestamp = tick[1] = tick[0];
						print_addi_status(0, -1, -1);
						print_addi_status(3, i, -1);
						player_stamina(i, 1, player[i].item.stamina_buf);
					}
				}
			}

			// �÷��̾� ���� ĭ �ٸ� �÷��̾� Ž�� (��.��.��.��) (�밢�� ���� X)
			for (int j = i + 1; j < n_player; j++)
			{
				if (((tick[0] - player[i].interact_timestamp > 1000) || (tick[0] - player[j].interact_timestamp > 1000)) &&
					(player[i].is_alive[0] && player[j].is_alive[0]) && (player[i].hasitem || player[j].hasitem) &&
					(player[i].stamina > 0 && player[j].stamina > 0) &&
					((((player[i].px + 1) == (player[j].px)) && ((player[i].py + 0) == (player[j].py))) ||
					(((player[i].px + 0) == (player[j].px)) && ((player[i].py + 1) == (player[j].py))) ||
					(((player[i].px - 1) == (player[j].px)) && ((player[i].py + 0) == (player[j].py))) ||
					(((player[i].px + 0) == (player[j].px)) && ((player[i].py - 1) == (player[j].py)))))
				{
					if (i == 0)
					{
						if (player[j].hasitem == false)
						{
							continue;
						}
						dialog(3, j);
					}
					else
					{
						fight = randint(0, 2);
					}

					if (fight == 2)
					{
						player[i].interact_timestamp = player[j].interact_timestamp = tick[1] = tick[0];
						continue;
					}

					ITEM item_temp;

					if (player[i].hasitem == false && player[j].hasitem == true)
					{
						if (fight == 0) // ��Ż
						{
							if ((player[i].str + player[i].item.str_buf) * (player[i].stamina / 100) >
								(player[j].str + player[j].item.str_buf) * (player[j].stamina / 100))
							{
								item_temp = player[i].item;
								player[i].item = player[j].item;
								player[j].item = item_temp;
								player[i].hasitem = true;
								player[j].hasitem = false;
								print_addi_status(0, -1, -1);
								print_addi_status(4, i, j);
								player_stamina(i, 1, player[i].item.stamina_buf - 40);
							}
							else
							{
								player_stamina(i, 1, -60);
							}
						}
						else if (fight = 1) // ȸ��
						{
							if ((player[i].intel + player[i].item.intel_buf) * (player[i].stamina / 100) >
								(player[j].intel + player[j].item.intel_buf) * (player[j].stamina / 100))
							{
								item_temp = player[i].item;
								player[i].item = player[j].item;
								player[j].item = item_temp;
								player[i].hasitem = true;
								player[j].hasitem = false;
								print_addi_status(0, -1, -1);
								print_addi_status(4, i, j);
								player_stamina(i, 1, player[i].item.stamina_buf - 20);
							}
							else
							{
								player_stamina(i, 1, -40);
							}
						}
					}
					else if (player[i].hasitem == true && player[j].hasitem == false)
					{
						if (fight == 0) // ��Ż
						{
							if ((player[i].str + player[i].item.str_buf) * (player[i].stamina / 100) >
								(player[j].str + player[j].item.str_buf) * (player[j].stamina / 100))
							{
								player_stamina(j, 1, -60);
							}
							else
							{
								item_temp = player[j].item;
								player[j].item = player[i].item;
								player[i].item = item_temp;
								player[j].hasitem = true;
								player[i].hasitem = false;
								print_addi_status(0, -1, -1);
								print_addi_status(4, j, i);
								player_stamina(j, 1, player[j].item.stamina_buf - 40);
							}
						}
						else if (fight = 1) // ȸ��
						{
							if ((player[i].intel + player[i].item.intel_buf) * (player[i].stamina / 100) >
								(player[j].intel + player[j].item.intel_buf) * (player[j].stamina / 100))
							{
								player_stamina(j, 1, -40);
							}
							else
							{
								item_temp = player[j].item;
								player[j].item = player[i].item;
								player[i].item = item_temp;
								player[j].hasitem = true;
								player[i].hasitem = false;
								print_addi_status(0, -1, -1);
								print_addi_status(4, j, i);
								player_stamina(j, 1, player[j].item.stamina_buf - 20);
							}
						}
					}
					else if (player[i].hasitem == true && player[j].hasitem == true)
					{
						if (randint(0, 1) || (i == 0)) // i�� �ֵ�
						{
							if (fight == 0) // ��Ż
							{
								if ((player[i].str + player[i].item.str_buf) * (player[i].stamina / 100) >
									(player[j].str + player[j].item.str_buf) * (player[j].stamina / 100))
								{
									item_temp = player[i].item;
									player[i].item = player[j].item;
									player[j].item = item_temp;
									print_addi_status(0, -1, -1);
									print_addi_status(4, i, j);
									player_stamina(i, 1, player[i].item.stamina_buf - 40);
								}
								else
								{
									player_stamina(i, 1, -60);
								}
							}
							else if (fight = 1) // ȸ��
							{
								if ((player[i].intel + player[i].item.intel_buf) * (player[i].stamina / 100) >
									(player[j].intel + player[j].item.intel_buf) * (player[j].stamina / 100))
								{
									item_temp = player[i].item;
									player[i].item = player[j].item;
									player[j].item = item_temp;
									print_addi_status(0, -1, -1);
									print_addi_status(4, i, j);
									player_stamina(i, 1, player[i].item.stamina_buf - 20);
								}
								else
								{
									player_stamina(i, 1, -40);
								}
							}
						}
						else // j�� �ֵ�
						{
							if (fight == 0) // ��Ż
							{
								if ((player[i].str + player[i].item.str_buf) * (player[i].stamina / 100) >
									(player[j].str + player[j].item.str_buf) * (player[j].stamina / 100))
								{
									player_stamina(j, 1, -60);
								}
								else
								{
									item_temp = player[j].item;
									player[j].item = player[i].item;
									player[i].item = item_temp;
									print_addi_status(0, -1, -1);
									print_addi_status(4, j, i);
									player_stamina(j, 1, player[j].item.stamina_buf - 40);
								}
							}
							else if (fight = 1) // ȸ��
							{
								if ((player[i].intel + player[i].item.intel_buf) * (player[i].stamina / 100) >
									(player[j].intel + player[j].item.intel_buf) * (player[j].stamina / 100))
								{
									player_stamina(j, 1, -40);
								}
								else
								{
									item_temp = player[j].item;
									player[j].item = player[i].item;
									player[i].item = item_temp;
									print_addi_status(0, -1, -1);
									print_addi_status(4, j, i);
									player_stamina(j, 1, player[j].item.stamina_buf - 20);
								}
							}
						}
						
					}
					player[i].interact_timestamp = player[j].interact_timestamp = tick[1] = tick[0];
				}
			}
		}
		display();
		Sleep(10);
		tick[0] += 10;
	}

	player_stamina(-1, 0, -1);
}

void nightgame_init(void)
{
	game_round = 2;

	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=80 lines=60");

	map_init(25, 80);

	for (int i = 0; i < n_player; i++) // �÷��̾� ��ġ
	{
		if (player[i].is_alive[0] == true)
		{
			do
			{
				x = randint(1, N_ROW - 2);
				y = randint(1, N_COL - 2);
			} while (!placable(x, y));

			player[i].px = x;
			player[i].py = y;
			player[i].period = randint(50, 100);

			back_buf[player[i].px][player[i].py] = '0' + i;  // (0 .. n_player-1)
		}
	}

	for (int i = 0; i < n_item ; i++) // ������ ��ġ
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));

		item[i].ix = x;
		item[i].iy = y;
	}

	nightgame_item_visable();

	display();

	debug_toggle = false;

	tick[0] = 0;
}