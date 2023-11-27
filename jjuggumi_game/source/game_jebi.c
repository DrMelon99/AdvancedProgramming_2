#include "games.h"

void jebi(void)
{
	jebi_init();

	dialog(0, -1);

	while (1) // 게임 진행 루프
	{


		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void jebi_init(void)
{
	game_round = 4;

	system("cls");

	map_init(7, 34);

	SetConsoleFontSize(20);
	system("mode con: cols=34 lines=15");
}