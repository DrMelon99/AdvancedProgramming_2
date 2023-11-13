#include "keyin.h"
#include "games.h"

void move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key)
	{
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
	if (!placable(nx, ny))
	{
		return;
	}
	move_tail(0, nx, ny);
}

void move_random(int player, int dir)
{
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do
	{
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void move_tail(int player, int nx, int ny)
{
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void move_random_mugunghwa(int player, int dir)
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

	move_tail_mugunghwa(p, nx, ny);
}

void move_tail_mugunghwa(int player, int nx, int ny)
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