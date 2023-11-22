#include "keyin.h"
#include "games.h"

// ★ 사용자 움직임 정의
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
	nx = player[0].px + dx[dir];
	ny = player[0].py + dy[dir];
	if (!placable(nx, ny))
	{
		return;
	}
	move_tail(0, nx, ny);
}

// ★ NPC 움직임 정의
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

// ★ back_buf[][]에 움직임 반영
void move_tail(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

// "무궁화 꽃이 피었습니다" 전용 NPC 움직임 정의
void move_random_mugunghwa(int p, int dir)
{
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do
	{
		if (randint(0, 1000) < 700) // NPC 앞으로 -> 70% / 영희의 킬모드가 켜질 경우 NPC 제자리 -> 70%
		{
			nx = player[p].px;
			if (yh_killmode == false)
			{
				ny = player[p].py - 1;
			}
			else
			{
				ny = player[p].py;
			}
		}
		else if (randint(0, 1000) >= 700 && randint(0, 1000) < 800) // NPC 위로 -> 10%
		{
			nx = player[p].px - 1;
			ny = player[p].py;
		}
		else if (randint(0, 1000) >= 800 && randint(0, 1000) < 900) // NPC 아래로 -> 10%
		{
			nx = player[p].px + 1;
			ny = player[p].py;
		}
		else // NPC 제자리 -> 10% / 영희의 킬모드가 켜질 경우 NPC 앞으로 10%
		{
			nx = player[p].px;
			if (yh_killmode == false)
			{
				ny = player[p].py;
			}
			else
			{
				ny = player[p].py - 1;
			}
		}
	} while (!placable(nx, ny));

	move_tail_mugunghwa(p, nx, ny);
}

// "무궁화 꽃이 피었습니다" 전용 화면 버퍼 처리
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

void move_random_nightgame(int p, int dir)
{
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do
	{
		nx = player[p].px + randint(-1, 1);
		ny = player[p].py + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail_nightgame(p, nx, ny);
	player[p].stamina--;
}

// ★ back_buf[][]에 움직임 반영
void move_tail_nightgame(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

// ★ 플레이어 스태미나 회복 관련
void player_stamina(int p, int opt)
{
	if (opt == 0) // 라운드 종료
	{
		player[p].stamina += randint(40, 50);

		if (player[p].stamina > 100)
		{
			player[p].stamina = 100;
		}
	}
	else if (opt == 1) // 아이템 획득
	{
		player[p].stamina = 100;
	}
}