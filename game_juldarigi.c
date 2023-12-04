#include "games.h"

void initializePlayerItem(ITEM* item) {
	item->id = 0;
	strcpy(item->name, "");  // 공백 문자열로 초기화
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

	//? 패자부활 할 떄 stamina몆에서 시작? 
	//? is_pass랑 hasitem 둘다 손봐줘야 하는거 맞나? 
	while (1) // 게임 진행 루프
	{
		for (int i = 0; i < 8; i++) { // 패자부활
			if (player[i].is_alive[0] == false) {
				player[i].hasitem = false;
				player[i].stamina = 1;
			}
		}

		for (int i = 0; i < 8; i++) { // 스태미나가 0인 플레이어 처리
			if (player[i].stamina == 0) {
				if (player[i].is_alive[0] == true) {
					player[i].is_pass = false;
					player[i].hasitem = false;
					// 플레이어가 아이템을 잃음
					initializePlayerItem(&(player[i].item));
					
				}
			}
			else {
				if (player[i].is_alive[0] == false) {
					// 플레이어 부활
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