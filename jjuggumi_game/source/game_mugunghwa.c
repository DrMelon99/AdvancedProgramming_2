#include "games.h"

void mugunghwa(void)
{
	int ment = 0;

	mugunghwa_init();

	dialog(0, -1);

	while (1)
	{
		// 'q'를 누르거나, 게임의 라운드가 5를 넘어가거나, 생존 인원이 한명일 경우
		if (player_control() || (game_cycle_count > 5) || (n_alive == 1))
			break;

		for (int i = 0; i < n_player; i++) // 탈락자 명단 비우기
		{
			player_outlist[i] = '\0';
		}

		npc_move_mugunghwa();

		player_visable();

		if (tick[1] < 6600) // "무궁화 꽃이 피었습니다" 멘트
		{
			for (int i = 0; i < 3; i++) // 영희 '#'
			{
				back_buf[6 + i][1] = '#';
			}

			switch (tick[1] / 100)
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
		else if (tick[1] > 6600 && tick[1] < 9000) // 영희 '@' 모양으로 바꾸고 킬 모드 ON
		{
			yh_killmode = true;

			for (int i = 0; i < 3; i++)
			{
				back_buf[6 + i][1] = '@';
			}
		}
		else if (tick[1] > 9000) // 킬 모드 이후 탈락자 발생 시, 탈락자 출력
		{
			// 현재 라운드 탈락자 검색
			for (int p = 0, i = 0; p < n_player; p++)
			{
				if (player[p].is_alive[0] != player[p].is_alive[1]) // 현재 생존 여부가 이전 생존 여부와 다르다면 탈락 리스트에 id채워넣기
				{
					player_outlist[i] = player[p].id;
					i++;
				}
				else // 아니면 '\0' 채워넣기
				{
					player_outlist[i] = '\0';
				}
			}

			if (ingame_exchange_data > 0) // 이번 라운드 탈락자 수가 0이상이면 탈락자 출력
			{
				dialog(1, -1);
				ingame_exchange_data = 0;
			}
				

			for (int p = 0, i = 0; p < n_player; p++)
			{
				if (player[p].is_alive[0] != player[p].is_alive[1])
					player[p].is_alive[1] = player[p].is_alive[0];
			}

			for (int i = 0; i < 30; i++) // 무궁화 멘트 지우기
			{
				back_buf[15][i] = '.';
			}
			display();
			for (int i = 0; i < 30; i++) // 무궁화 멘트 지우기
			{
				back_buf[15][i] = ' ';
			}

			yh_killmode = false;

			tick[1] = ment = 0; // 틱 초기화
			game_cycle_count++;
		}

		display();
		Sleep(10);
		tick[0] += 10;
		tick[1] += 10;
	}

	yh_killmode = false;

	for (int i = 0; i < n_player; i++)
		player[i].is_pass = false;

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
	game_cycle_count = ingame_exchange_data = 0;
	int sound = 0;

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

	debug_toggle = false;

	tick[0] = tick[1] = 10;
}