#include "games.h"

void juldarigi(void)
{
	juldarigi_init();

	dialog(0, -1);

	while (1) // 게임 진행 루프
	{
		if (player_control())
			break;

		player_visable();

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void juldarigi_init(void)
{
	game_round = 3;

	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=80 lines=50");
}