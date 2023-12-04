#include "games.h"

void juldarigi(void)
{
	juldarigi_init();

	dialog(0, -1);
	
	system("cls");

	map_init(3, 32);
		
	while (1) // 게임 진행 루프
	{
		for (int i = 0; i < 8; i++) { 
			if (player[i].is_alive[0] == false) {
				player[i].hasitem = false;
				player[i].stamina = 1;
			}
		}
		for (int i = 0; i < 8; i++) {
			if (player[i].stamina == 0) {
				if (player[i].is_alive[0] == true) {
					player[i].is_pass = false;
					player[i].hasitem = false;

					initializePlayerItem(&(player[i].item));

				}
			}
			else {
				if (player[i].is_alive[0] == false) {
					player[i].is_pass = true;
					player[i].is_alive[0] = true;
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