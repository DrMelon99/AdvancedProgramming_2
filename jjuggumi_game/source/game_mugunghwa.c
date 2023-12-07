#include "games.h"

void mugunghwa(void)
{
	int ment = 0;

	mugunghwa_init();

	dialog(0, -1);

	while (1)
	{
		// 'q'�� �����ų�, ������ ���尡 5�� �Ѿ�ų�, ���� �ο��� �Ѹ��� ���
		if (player_control() || (game_cycle_count > 5) || (n_alive == 1))
			break;

		for (int i = 0; i < n_player; i++) // Ż���� ��� ����
		{
			player_outlist[i] = '\0';
		}

		npc_move_mugunghwa();

		player_visable();

		if (tick[1] < 6600) // "����ȭ ���� �Ǿ����ϴ�" ��Ʈ
		{
			for (int i = 0; i < 3; i++) // ���� '#'
			{
				back_buf[6 + i][1] = '#';
			}

			switch (tick[1] / 100)
			{
			case 5:
				while (ment < 3)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 15:
				while (ment < 6)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 25:
				while (ment < 9)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 35:
				while (ment < 12)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 45:
				while (ment < 15)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 52:
				while (ment < 18)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 57:
				while (ment < 21)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 60:
				while (ment < 24)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 63:
				while (ment < 27)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			case 65:
				while (ment < 30)
					back_buf[15][ment] = MUGUNWHA_MENT[ment++];
				break;
			}
		}
		else if (tick[1] > 6600 && tick[1] < 9000) // ���� '@' ������� �ٲٰ� ų ��� ON
		{
			yh_killmode = true;

			for (int i = 0; i < 3; i++)
			{
				back_buf[6 + i][1] = '@';
			}
		}
		else if (tick[1] > 9000) // ų ��� ���� Ż���� �߻� ��, Ż���� ���
		{
			// ���� ���� Ż���� �˻�
			for (int p = 0, i = 0; p < n_player; p++)
			{
				if (player[p].is_alive[0] != player[p].is_alive[1]) // ���� ���� ���ΰ� ���� ���� ���ο� �ٸ��ٸ� Ż�� ����Ʈ�� idä���ֱ�
				{
					player_outlist[i] = player[p].id;
					i++;
				}
				else // �ƴϸ� '\0' ä���ֱ�
				{
					player_outlist[i] = '\0';
				}
			}

			if (ingame_exchange_data > 0) // �̹� ���� Ż���� ���� 0�̻��̸� Ż���� ���
			{
				dialog(1, -1);
				ingame_exchange_data = 0;
			}
				

			for (int p = 0, i = 0; p < n_player; p++)
			{
				if (player[p].is_alive[0] != player[p].is_alive[1])
					player[p].is_alive[1] = player[p].is_alive[0];
			}

			for (int i = 0; i < 30; i++) // ����ȭ ��Ʈ �����
			{
				back_buf[15][i] = '.';
			}
			display();
			for (int i = 0; i < 30; i++) // ����ȭ ��Ʈ �����
			{
				back_buf[15][i] = ' ';
			}

			yh_killmode = false;

			tick[1] = ment = 0; // ƽ �ʱ�ȭ
			game_cycle_count++;
		}

		display();
		Sleep(10);
		tick[0] += 10;
		tick[1] += 10;
	}

	yh_killmode = false;

	for (int i = 0; i < n_player; i++)
		player[i].is_pass = false;

	player_stamina(-1, 0, -1);
}

void mugunghwa_init(void)
{
	game_round = 1;

	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	// ��� �÷��̾� ���� ��� ���� false �ʱ� ����
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_pass = false;
	}

	// "����ȭ ���� �Ǿ����ϴ�" ���� �� 0���� �ʱ�ȭ
	game_cycle_count = ingame_exchange_data = 0;
	int sound = 0;

	// ���� ��ġ
	for (int i = 0; i < 3; i++)
	{
		back_buf[6 + i][1] = '#';
	}

	// n���� �÷��̾���� ���� ���� ������ ���� ��ġ
	int x, y;
	for (int i = 0; i < n_player; i++)
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = (N_COL - 2);
		} while (!placable(x, y));

		player[i].px = x;
		player[i].py = y;
		player[i].period = randint(100, 500);

		back_buf[player[i].px][player[i].py] = '0' + i;
	}

	display();

	debug_toggle = false;

	tick[0] = tick[1] = 10;
}