#include "games.h"

void mugunghwa(void)
{
	mugunghwa_init();

	display();

	dialog(0, -1);

	while (1)
	{
		// ������ "����ȭ ���� �Ǿ����ϴ�" ���ϱ� �� ���� ��ȯ
		younghee();

		// ����� ������ Ű�Է�
		key_t key = get_key();
		if ((key == K_QUIT) || (n_alive == 1) || (count > 3))
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			move_manual(key);
		}

		// �ٸ� NPC ���� ������ �۵�
		for (int i = 1; i < n_player; i++)
		{
			if (tick[0] % player[i].period == 0)
			{
				move_random_mugunghwa(i, -1);
			}
		}

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void mugunghwa_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	// ��� �÷��̾� ���� ��� ���� false �ʱ� ����
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_pass = false;
	}

	// "����ȭ ���� �Ǿ����ϴ�" ����� ��� �÷��̾� �� 0���� �ʱ�ȭ
	count = pass_n_player = 0;


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

		back_buf[player[i].px][player[i].py] = '0' + i;  // (0 .. n_player-1)
	}

	tick[0] = 0;
}

void younghee(void)
{
	int ment = 0;

	if (tick[0] < 6600)
	{
		for (int i = 0; i < 3; i++) // ���� '#'
		{
			back_buf[6 + i][1] = '#';
		}

		switch (tick[0] / 100)
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
	else if (tick > 6600 && tick < 9000)
	{
		yh_killmode = true;

		for (int i = 0; i < 3; i++) // ���� '@'
		{
			back_buf[6 + i][1] = '@';
		}
	}
	else if (tick > 9000) // �й��� ���
	{
		// Ż���� �˻�
		if (n_alivepost != n_alive)
		{
			n_alivepost = n_alive; // �������� ����ȭ

			for (int i = 0; i < n_player; i++)
			{
				player_outlist[i] = 'v';
			}

			for (int i = 0, j = 0; i < n_player; i++)
			{
				if (player_statuspost[i] != player[i].is_alive)
				{
					player_statuspost[i] = player[i].is_alive;
					player_outlist[j++] = i;
				}
			}

			dialog(1, -1);
		}

		for (int i = 0; i < 30; i++) // ����ȭ ��Ʈ �����
		{
			back_buf[15][i] = '.';
		}
		display();
		for (int i = 0; i < 30; i++)
		{
			back_buf[15][i] = ' ';
		}

		yh_killmode = false;
		tick[0] = 0; // ƽ �ʱ�ȭ
		count++;
	}
}