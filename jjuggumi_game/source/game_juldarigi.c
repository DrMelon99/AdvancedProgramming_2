#include "games.h"

void initializePlayerItem(ITEM* item) {
	item->id = 0;
	item->name[0] = '\0';  // �� ���ڿ��� �ʱ�ȭ
	item->getable = false;
	item->ix = 0;
	item->iy = 0;
	item->intel_buf = 0;
	item->str_buf = 0;
	item->stamina_buf = 0;
}

void juldarigi(void)
{
	juldarigi_init();

	dialog(0, -1);
	
	system("cls");

	map_init_juldarigi(3, 32);
		
	while (1) // ���� ���� ����
	{
		for (int i = 0; i < n_player; i++) { // ���� ��Ȱ 
			player[i].is_alive[1] = player[i].is_alive[0];
			if (player[i].is_alive[0] == false) {
				player[i].is_alive[0] = true;
			}
		}


		for (int i = 0; i < n_player; i++) { // ���� ���� �� 
			if (player[i].stamina == 0) { 
				// stamina = 0 �̸� player[i].is_alive[0] == false�ε� 
				// player[i].is_alive[1] == true�Ͻ� ���ں�Ȱ�������� Ż�� ���� �׳� �̷��Ը� ���൵? 
				if (player[i].is_alive[1] == true) {
					initializePlayerItem(&(player[i].item));
				}
				else {
					player[i].is_alive[0] = false;
				}
			}

		}

		display();
		Sleep(10);
		tick[0] += 10;
	}
}  

void map_init_juldarigi(int n_row, int n_col)
{
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;

	for (int i = 0; i < N_ROW; i++)
	{
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++)
		{
			// ��� �ո� �κ��� �������� ä���
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}

	// �߾� �� ��� �ո� �κ��� �������� ����  - �̺κ� ������ �ȵ�..
	int center_col = N_COL / 2;
	for (int i = 1; i < N_ROW - 1; i++)
	{
		back_buf[i][center_col] = ' ';
	}
}

void juldarigi_init(void)
{
	game_round = 3;

	system("cls");

	map_init_juldarigi(9, 32);

	SetConsoleFontSize(20);
	system("mode con: cols=32 lines=30");
}