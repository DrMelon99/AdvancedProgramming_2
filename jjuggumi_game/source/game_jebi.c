#include "games.h"

void jebi(void)
{
	jebi_init();

	dialog(0, -1);

	while (1) // 게임 진행 루프
	{
		if ((n_alive == 1) || (break_cmd == true))
			break;

		for (int i = 0; i < n_player; i++)
		{
			if (player[i].is_alive[0] == true)
			{
				ingame_exchange_data = player[i].id; // 상태 창에 출력하기 위해 데이터 교환

				if (jebi_select())
				{
					break_cmd = true;
					break;
				}
				
				jebis[jebi_sel][1] = 1; // 개봉함

				if (jebis[jebi_sel][0] == 0) // 탈락 제비 뽑았을 때
				{
					player[player[i].id].is_alive[0] = false;

					n_alive--;

					dialog(4, player[player[i].id].id);

					break;
				}
				else // 통과 제비 뽑았을 때
				{
					dialog(4, player[i].id);
					player[i].is_pass = true;
				}
			}
		}

		system("cls");
		map_init(7, 45);

		jebi_mix();

		for(int i = 0 ; i < n_player ; i++)
			player[i].is_pass = false;

		game_cycle_count++;

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void jebi_init(void)
{
	game_round = 4;

	system("cls");

	map_init(7, 45);

	SetConsoleFontSize(20);
	system("mode con: cols=45 lines=35");

	game_cycle_count = 0;

	break_cmd = false;

	jebi_mix();

	for (int i = 0; i < n_player; i++)
		player[i].is_pass = false;

	display();

	debug_toggle = false;

	ingame_exchange_data = 0;

	tick[0] = 0;
}