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
	system("cls");


}