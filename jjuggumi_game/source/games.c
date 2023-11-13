#include "keyin.h"
#include "games.h"

void move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key)
	{
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
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
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	do
	{
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]�� ���
void move_tail(int player, int nx, int ny)
{
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void move_random_mugunghwa(int player, int dir)
{
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
	do
	{
		if (randint(0, 1000) < 700) // NPC ������ -> 70% / ������ ų��尡 ���� ��� NPC ���ڸ� -> 70%
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
		else if (randint(0, 1000) >= 700 && randint(0, 1000) < 800) // NPC ���� -> 10%
		{
			nx = px[p] - 1;
			ny = py[p];
		}
		else if (randint(0, 1000) >= 800 && randint(0, 1000) < 900) // NPC �Ʒ��� -> 10%
		{
			nx = px[p] + 1;
			ny = py[p];
		}
		else // NPC ���ڸ� -> 10% / ������ ų��尡 ���� ��� NPC ������ 10%
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
	int p = player;  // �̸��� ��...

	if ((yh_killmode == false) || ((back_buf[nx][ny] == back_buf[px[p]][py[p]]))) // ų��� ����, ������ ����
	{
		if ((ny == 1) || (ny == 2 && (nx > 5 && nx < 9))) // ����ϸ� ���ֱ�
		{
			pass_n_player++;
			back_buf[nx][ny] = ' '; // ���ֱ�
			back_buf[px[p]][py[p]] = ' '; // �̵� �� ���� �����
			px[p] = nx;
			py[p] = ny;
		}
		else
		{
			back_buf[nx][ny] = back_buf[px[p]][py[p]]; // �̵�
			back_buf[px[p]][py[p]] = ' '; // �̵� �� ���� �����
			px[p] = nx;
			py[p] = ny;
		}
	}
	else if ((yh_killmode == true))
	{
		for (int i = 1; i < 10; i++)
		{
			if (player_status[i] && ((ny > py[i]) && (nx == px[i]))) // ���� �ذ�
			{
				back_buf[nx][ny] = back_buf[px[p]][py[p]]; // �̵�
				back_buf[px[p]][py[p]] = ' '; // �̵� �� ���� �����
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