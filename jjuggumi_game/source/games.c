#include "keyin.h"
#include "games.h"

bool player_control(void)
{
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)

	key_t key = get_key();
	if (key == K_QUIT)
	{
		return true;
	}
	else if (key == K_SPACE)
	{
		return false;
	}
	else if ((key != K_UNDEFINED))
	{
		switch (key)
		{
		case K_UP: dir = DIR_UP; break;
		case K_DOWN: dir = DIR_DOWN; break;
		case K_LEFT: dir = DIR_LEFT; break;
		case K_RIGHT: dir = DIR_RIGHT; break;
		}

		int nx = player[0].px + dx[dir];
		int ny = player[0].py + dy[dir];

		if (!placable(nx, ny))
		{
			return false;
		}
		move_tail(0, nx, ny);

		return false;
	}
}

void move_random(int p, int dir)
{
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do
	{
		nx = player[p].px + randint(-1, 1);
		ny = player[p].py + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void move_tail(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

void player_visable(void)
{
	for (int i = 0; i < n_player; i++)
	{
		if ((player[i].is_alive == true) && (player[i].is_pass == false))
		{
			back_buf[player[i].px][player[i].py] = '0' + i;
		}
		else
		{
			back_buf[player[i].px][player[i].py] = ' ';
		}
	}
}

void player_stamina(int p, int opt, int stamina_val)
{
	if (opt == 0) // 라운드 종료
	{
		for (int i = 0; i < n_player; i++)
		{
			player[i].stamina += randint(40, 50);

			if (player[i].stamina > 100)
			{
				player[i].stamina = 100;
			}
			else if (player[i].stamina < 0)
			{
				player[i].stamina = 0;
			}
		}
	}
	else if (opt == 1) // 특정 플레리어 스태미나 조정
	{
		player[p].stamina += stamina_val;

		if (player[p].stamina > 100)
		{
			player[p].stamina = 100;
		}
		else if (player[p].stamina < 0)
		{
			player[p].stamina = 0;
		}
	}
}

void npc_move_mugunghwa(void)
{
	int nx, ny;  // 다음에 놓일 자리

	for (int i = 1; i < n_player; i++)
	{
		if (tick[0] % player[i].period == 0)
		{
			do
			{
				if (randint(0, 100) < 70) // NPC 앞으로 -> 70% / 영희의 킬모드가 켜질 경우 NPC 제자리 -> 70%
				{
					nx = player[i].px;
					if (yh_killmode == false)
					{
						ny = player[i].py - 1;
					}
					else
					{
						ny = player[i].py;
					}
				}
				else if (randint(0, 100) >= 70 && randint(0, 100) < 80) // NPC 위로 -> 10%
				{
					nx = player[i].px - 1;
					ny = player[i].py;
				}
				else if (randint(0, 100) >= 80 && randint(0, 100) < 90) // NPC 아래로 -> 10%
				{
					nx = player[i].px + 1;
					ny = player[i].py;
				}
				else // NPC 제자리 -> 10% / 영희의 킬모드가 켜질 경우 NPC 앞으로 10%
				{
					nx = player[i].px;
					if (yh_killmode == false)
					{
						ny = player[i].py;
					}
					else
					{
						ny = player[i].py - 1;
					}
				}
			} while (!placable(nx, ny));

			move_tail_mugunghwa(i, nx, ny);
		}
	}
}

void move_tail_mugunghwa(int p, int nx, int ny)
{
	if ((yh_killmode == false) || ((back_buf[nx][ny] == back_buf[player[p].px][player[p].py]))) // 킬모드 꺼짐, 가만히 있음
	{
		if ((ny == 1) || (ny == 2 && (nx > 5 && nx < 9))) // 통과하면 없애기
		{
			pass_n_player++;
			back_buf[nx][ny] = ' '; // 없애기
			back_buf[player[p].px][player[p].py] = ' '; // 이동 전 흔적 지우기
			player[p].px = nx;
			player[p].py = ny;
		}
		else
		{
			back_buf[nx][ny] = back_buf[player[p].px][player[p].py]; // 이동
			back_buf[player[p].px][player[p].py] = ' '; // 이동 전 흔적 지우기
			player[p].px = nx;
			player[p].py = ny;
		}
	}
	else if ((yh_killmode == true))
	{
		for (int i = 1; i < 10; i++)
		{
			if (player[i].is_alive && ((ny > player[i].py) && (nx == player[i].px))) // 문제 해결
			{
				back_buf[nx][ny] = back_buf[player[p].px][player[p].py]; // 이동
				back_buf[player[p].px][player[p].py] = ' '; // 이동 전 흔적 지우기
				player[p].px = nx;
				player[p].py = ny;
				break;
			}
			else
			{
				player[i].is_alive = false;
				n_alive--;
				back_buf[player[p].px][player[p].py] = ' ';
				break;
			}
		}
	}
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

void npc_move_nightgame(void)
{
	int nx, ny;  // 다음에 놓일 자리

	for (int i = 1; i < n_player; i++)
	{
		if (tick[0] % player[i].period == 0)
		{
			do
			{
				nx = player[i].px + randint(-1, 1);
				ny = player[i].py + randint(-1, 1);
			} while (!placable(nx, ny));

			move_tail_nightgame(i, nx, ny);
		}
	}
}

void move_tail_nightgame(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

void nightgame_item_visable(void)
{
	for (int i = 0; i < n_item; i++)
	{
		// getable 여부에 따른 아이템 시각화
		if (item[i].getable == true)
		{
			back_buf[item[i].ix][item[i].iy] = '$';
		}
		else if (back_buf[item[i].ix][item[i].iy] == '$')
		{
			back_buf[item[i].ix][item[i].iy] = ' ';
		}
	}
}