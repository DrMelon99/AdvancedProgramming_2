#include "games.h"

void juldarigi(void)
{
	juldarigi_init();

	display();

	while (1)
	{


		display();
		Sleep(10);
		tick += 10;
	}

}

void juldarigi_init(void)
{
	system("cls");


}