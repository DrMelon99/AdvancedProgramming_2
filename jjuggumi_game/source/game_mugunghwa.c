#include "games.h"

void mugunghwa(void)
{
	mugunghwa_init();

	dialog(0, -1);

	while (1)
	{
		if (player_control())
			break;

		npc_move_mugunghwa();

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
			player_control(key);
		}

		// �ٸ� NPC ���� ������ �۵�
		for (int i = 1; i < n_player; i++)
		{
			if (tick[0] % player[i].period == 0)
			{
				npc_move_mugunghwa(i, -1);
			}
		}

		display();
		Sleep(10);
		tick[0] += 10;
	}

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

	display();

	tick[0] = 0;
}