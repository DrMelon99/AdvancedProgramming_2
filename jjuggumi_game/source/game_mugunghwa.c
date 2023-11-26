#include "games.h"

void mugunghwa(void)
{
	mugunghwa_init();

	dialog(0, -1);

	while (1)
	{
		if (player_control() || (count > 3)/* || (�����ڰ� �Ѹ��� ��)*/)
			break;

		npc_move_mugunghwa();

		// ������ "����ȭ ���� �Ǿ����ϴ�" ���ϱ� �� ���� ��ȯ
		younghee();

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

	// "����ȭ ���� �Ǿ����ϴ�" ���� �� 0���� �ʱ�ȭ
	count = 0;

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

	tick[0] = 0;
}