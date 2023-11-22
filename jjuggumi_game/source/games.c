#include "keyin.h"
#include "games.h"

// �� ����� ������ ����
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
	nx = player[0].px + dx[dir];
	ny = player[0].py + dy[dir];
	if (!placable(nx, ny))
	{
		return;
	}
	move_tail(0, nx, ny);
}

// �� NPC ������ ����
void move_random(int p, int dir)
{
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
	do
	{
		nx = player[p].px + randint(-1, 1);
		ny = player[p].py + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// �� back_buf[][]�� ������ �ݿ�
void move_tail(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

// "����ȭ ���� �Ǿ����ϴ�" ���� NPC ������ ����
void move_random_mugunghwa(int p, int dir)
{
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
	do
	{
		if (randint(0, 1000) < 700) // NPC ������ -> 70% / ������ ų��尡 ���� ��� NPC ���ڸ� -> 70%
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
		else if (randint(0, 1000) >= 700 && randint(0, 1000) < 800) // NPC ���� -> 10%
		{
			nx = player[p].px - 1;
			ny = player[p].py;
		}
		else if (randint(0, 1000) >= 800 && randint(0, 1000) < 900) // NPC �Ʒ��� -> 10%
		{
			nx = player[p].px + 1;
			ny = player[p].py;
		}
		else // NPC ���ڸ� -> 10% / ������ ų��尡 ���� ��� NPC ������ 10%
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

// "����ȭ ���� �Ǿ����ϴ�" ���� ȭ�� ���� ó��
void move_tail_mugunghwa(int p, int nx, int ny)
{
	if ((yh_killmode == false) || ((back_buf[nx][ny] == back_buf[player[p].px][player[p].py]))) // ų��� ����, ������ ����
	{
		if ((ny == 1) || (ny == 2 && (nx > 5 && nx < 9))) // ����ϸ� ���ֱ�
		{
			pass_n_player++;
			back_buf[nx][ny] = ' '; // ���ֱ�
			back_buf[player[p].px][player[p].py] = ' '; // �̵� �� ���� �����
			player[p].px = nx;
			player[p].py = ny;
		}
		else
		{
			back_buf[nx][ny] = back_buf[player[p].px][player[p].py]; // �̵�
			back_buf[player[p].px][player[p].py] = ' '; // �̵� �� ���� �����
			player[p].px = nx;
			player[p].py = ny;
		}
	}
	else if ((yh_killmode == true))
	{
		for (int i = 1; i < 10; i++)
		{
			if (player[i].is_alive && ((ny > player[i].py) && (nx == player[i].px))) // ���� �ذ�
			{
				back_buf[nx][ny] = back_buf[player[p].px][player[p].py]; // �̵�
				back_buf[player[p].px][player[p].py] = ' '; // �̵� �� ���� �����
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
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
	do
	{
		nx = player[p].px + randint(-1, 1);
		ny = player[p].py + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail_nightgame(p, nx, ny);
	player[p].stamina--;
}

// �� back_buf[][]�� ������ �ݿ�
void move_tail_nightgame(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

// �� �÷��̾� ���¹̳� ȸ�� ����
void player_stamina(int p, int opt)
{
	if (opt == 0) // ���� ����
	{
		player[p].stamina += randint(40, 50);

		if (player[p].stamina > 100)
		{
			player[p].stamina = 100;
		}
	}
	else if (opt == 1) // ������ ȹ��
	{
		player[p].stamina = 100;
	}
}