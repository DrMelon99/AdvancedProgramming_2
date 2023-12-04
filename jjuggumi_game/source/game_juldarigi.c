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

	map_init(3, 32);
		
	while (1) // ���� ���� ����
	{
		for (int i = 0; i < 8; i++) { // ���� ��Ȱ 
			player[i].is_alive[1] = player[i].is_alive[0];
			if (player[i].is_alive[0] == false) {
				player[i].is_alive[0] = true;
			}
		}


		for (int i = 0; i < 8; i++) { // ���� ���� �� 
			if (player[i].stamina == 0) { 
				// stamina = 0 �̸� player[i].is_alive[0] == false�ε� 
				// player[i].is_alive[1] == true�Ͻ� ���ں�Ȱ�������� Ż�� ���� �׳� �̷��Ը� ���൵? 
				if (player[i].is_alive[1] == true) {
					initializePlayerItem(&(player[i].item));
				}
				else {
					player[i].is_alive[0] == false;
				}
			}

		}

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void juldarigi_init(void)
{
	game_round = 3;

	system("cls");

	map_init(9, 32);

	SetConsoleFontSize(20);
	system("mode con: cols=32 lines=30");
}