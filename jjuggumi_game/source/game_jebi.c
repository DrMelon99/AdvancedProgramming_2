#include "games.h"

void jebi(void)
{
	jebi_init();

	display();

	while (1)
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

	SetConsoleFontSize(20);
	system("mode con: cols=80 lines=50");
}