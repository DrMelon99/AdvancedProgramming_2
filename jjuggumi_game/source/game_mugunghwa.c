#include "games.h"

void mugunghwa(void)
{
	mugunghwa_init();

	display();

	dialog(0, -1);

	while (1)
	{
		// 영희의 "무궁화 꽃이 피었습니다" 말하기 및 상태 전환
		younghee();

		// 사용자 움직임 키입력
		key_t key = get_key();
		if ((key == K_QUIT) || (n_alive == 1) || (count > 3))
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			move_manual(key);
		}

		// 다른 NPC 랜덤 움직임 작동
		for (int i = 1; i < n_player; i++)
		{
			if (tick[0] % player[i].period == 0)
			{
				move_random_mugunghwa(i, -1);
			}
		}

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void mugunghwa_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	// 모든 플레이어 게임 통과 여부 false 초기 설정
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_pass = false;
	}

	// "무궁화 꽃이 피었습니다" 라운드와 통과 플레이어 수 0으로 초기화
	count = pass_n_player = 0;


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

		back_buf[player[i].px][player[i].py] = '0' + i;  // (0 .. n_player-1)
	}

	tick[0] = 0;
}

void younghee(void)
{
	int ment = 0;

	if (tick[0] < 6600)
	{
		for (int i = 0; i < 3; i++) // 영희 '#'
		{
			back_buf[6 + i][1] = '#';
		}

		switch (tick[0] / 100)
		{
		case 5:
			while (ment < 3)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 15:
			while (ment < 6)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 25:
			while (ment < 9)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 35:
			while (ment < 12)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 45:
			while (ment < 15)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 52:
			while (ment < 18)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 57:
			while (ment < 21)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 60:
			while (ment < 24)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 63:
			while (ment < 27)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		case 65:
			while (ment < 30)
				back_buf[15][ment] = MUGUNWHA_MENT[ment++];
			break;
		}
	}
	else if (tick > 6600 && tick < 9000)
	{
		yh_killmode = true;

		for (int i = 0; i < 3; i++) // 영희 '@'
		{
			back_buf[6 + i][1] = '@';
		}
	}
	else if (tick > 9000) // 패배자 출력
	{
		// 탈락자 검색
		if (n_alivepost != n_alive)
		{
			n_alivepost = n_alive; // 이전값과 동기화

			for (int i = 0; i < n_player; i++)
			{
				player_outlist[i] = 'v';
			}

			for (int i = 0, j = 0; i < n_player; i++)
			{
				if (player_statuspost[i] != player[i].is_alive)
				{
					player_statuspost[i] = player[i].is_alive;
					player_outlist[j++] = i;
				}
			}

			dialog(1, -1);
		}

		for (int i = 0; i < 30; i++) // 무궁화 멘트 지우기
		{
			back_buf[15][i] = '.';
		}
		display();
		for (int i = 0; i < 30; i++)
		{
			back_buf[15][i] = ' ';
		}

		yh_killmode = false;
		tick[0] = 0; // 틱 초기화
		count++;
	}
}