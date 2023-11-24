#include "games.h"

void juldarigi(void)
{
	juldarigi_init();

	display();

	while (1)
	{


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