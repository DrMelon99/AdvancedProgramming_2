#include "games.h"

void move_random(int player, int dir)
{
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do
	{
		if (randint(0, 1000) < 700) // NPC 앞으로 -> 70% / 영희의 킬모드가 켜질 경우 NPC 제자리 -> 70%
		{
			nx = px[p];
			if (yh_killmode == false)
			{
				ny = py[p] - 1;
			}
			else
			{
				ny = py[p];
			}
		}
		else if (randint(0, 1000) >= 700 && randint(0, 1000) < 800) // NPC 위로 -> 10%
		{
			nx = px[p] - 1;
			ny = py[p];
		}
		else if (randint(0, 1000) >= 800 && randint(0, 1000) < 900) // NPC 아래로 -> 10%
		{
			nx = px[p] + 1;
			ny = py[p];
		}
		else // NPC 제자리 -> 10% / 영희의 킬모드가 켜질 경우 NPC 앞으로 10%
		{
			nx = px[p];
			if (yh_killmode == false)
			{
				ny = py[p];
			}
			else
			{
				ny = py[p] - 1;
			}
		}
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void move_tail(int player, int nx, int ny)
{
	int p = player;  // 이름이 길어서...

	if ((yh_killmode == false) || ((back_buf[nx][ny] == back_buf[px[p]][py[p]]))) // 킬모드 꺼짐, 가만히 있음
	{
		if ((ny == 1) || (ny == 2 && (nx > 5 && nx < 9))) // 통과하면 없애기
		{
			pass_n_player++;
			back_buf[nx][ny] = ' '; // 없애기
			back_buf[px[p]][py[p]] = ' '; // 이동 전 흔적 지우기
			px[p] = nx;
			py[p] = ny;
		}
		else
		{
			back_buf[nx][ny] = back_buf[px[p]][py[p]]; // 이동
			back_buf[px[p]][py[p]] = ' '; // 이동 전 흔적 지우기
			px[p] = nx;
			py[p] = ny;
		}
	}
	else if ((yh_killmode == true))
	{
		for (int i = 1; i < 10; i++)
		{
			if (player_status[i] && ((ny > py[i]) && (nx == px[i]))) // 문제 해결
			{
				back_buf[nx][ny] = back_buf[px[p]][py[p]]; // 이동
				back_buf[px[p]][py[p]] = ' '; // 이동 전 흔적 지우기
				px[p] = nx;
				py[p] = ny;
				break;
			}
			else
			{
				player_status[p] = false;
				n_alive--;
				back_buf[px[p]][py[p]] = ' ';
				break;
			}
		}
	}
}

void move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}


	move_tail(0, nx, ny);
}

void mugunghwa(void)
{
	mugunghwa_init();
	display();

	// 게임 시작 타이머
	for (int i = DIALOG_DURATION_SEC; i > -1; i--)
	{
		dialog(0, i);
	}

	while (1)
	{
		// 영희의 "무궁화 꽃이 피었습니다" 말하기 및 상태 전환
		younghee();

		// 사용자 움직임 키입력
		key_t key = get_key();
		if ((key == K_QUIT) || (n_alive == 1) || (count > 3) || (pass_n_player == n_alive))
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
			if (tick % period[i] == 0)
			{
				move_random(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}

void mugunghwa_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=60 lines=40");

	map_init(15, 60);

	count = pass_n_player = 0;


	// 영희 배치
	for (int i = 0; i < 3; i++)
	{
		back_buf[6 + i][1] = '#';
	}

	// n명의 플레이어들을 우측 시작 지점에 랜덤 배치
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = (N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}

void younghee(void)
{
	int ment = 0;

	if (tick < 6600)
	{
		for (int i = 0; i < 3; i++) // 영희 '#'
		{
			back_buf[6 + i][1] = '#';
		}

		switch (tick / 100)
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
				if (player_statuspost[i] != player_status[i])
				{
					player_statuspost[i] = player_status[i];
					player_outlist[j++] = i;
				}
			}

			dialog(1, 1);
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
		tick = 0; // 틱 초기화
		count++;
	}
}