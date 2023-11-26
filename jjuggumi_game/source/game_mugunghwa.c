#include "games.h"

void mugunghwa(void)
{
	mugunghwa_init();

	dialog(0, -1);

	while (1)
	{
		if (player_control() || (count > 3)/* || (생존자가 한명일 때)*/)
			break;

		npc_move_mugunghwa();

		// 영희의 "무궁화 꽃이 피었습니다" 말하기 및 상태 전환
		younghee();

		display();
		Sleep(10);
		tick[0] += 10;
	}

	player_stamina(-1, 0, -1);
}

void mugunghwa_init(void)
{
	game_round = 1;

	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	// 모든 플레이어 게임 통과 여부 false 초기 설정
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_pass = false;
	}

	// "무궁화 꽃이 피었습니다" 라운드 수 0으로 초기화
	count = 0;

	// 영희 배치
	for (int i = 0; i < 3; i++)
	{
		back_buf[6 + i][1] = '#';
	}

	// n명의 플레이어들을 우측 시작 지점에 랜덤 배치
	int x, y;
	for (int i = 0; i < n_player; i++)
	{
		do
		{
			x = randint(1, N_ROW - 2);
			y = (N_COL - 2);
		} while (!placable(x, y));

		player[i].px = x;
		player[i].py = y;
		player[i].period = randint(100, 500);

		back_buf[player[i].px][player[i].py] = '0' + i;
	}

	display();

	tick[0] = 0;
}