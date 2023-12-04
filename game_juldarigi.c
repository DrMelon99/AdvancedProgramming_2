#include "games.h"

void initializePlayerItem(ITEM* item) {
	item->id = 0;
	strcpy(item->name, "");  // ���� ���ڿ��� �ʱ�ȭ
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

	//? ���ں�Ȱ �� �� stamina�p���� ����? 
	//? is_pass�� hasitem �Ѵ� �պ���� �ϴ°� �³�? 
	while (1) // ���� ���� ����
	{
		for (int i = 0; i < 8; i++) { // ���ں�Ȱ
			if (player[i].is_alive[0] == false) {
				player[i].hasitem = false;
				player[i].stamina = 1;
			}
		}

		for (int i = 0; i < 8; i++) { // ���¹̳��� 0�� �÷��̾� ó��
			if (player[i].stamina == 0) {
				if (player[i].is_alive[0] == true) {
					player[i].is_pass = false;
					player[i].hasitem = false;
					// �÷��̾ �������� ����
					initializePlayerItem(&(player[i].item));
					
				}
			}
			else {
				if (player[i].is_alive[0] == false) {
					// �÷��̾� ��Ȱ
					player[i].is_pass = true;
					player[i].is_alive[0] = true;
				}
			}


			display();
			Sleep(10);
			tick[0] += 10;
		}
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