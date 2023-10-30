#pragma warning(disable : 4996)

#include <string.h>
#include "jjuggumi.h"
#include "keyin.h"
#include "canvas.h"
#include "media.h"

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void move_random(int player, int dir)
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

	move_tail(p, nx, ny);
}

// back_buf[][]�� ���
void move_tail(int player, int nx, int ny)
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
	else if((yh_killmode == true))
	{
		for (int i = 1; i < 10 ; i++)
		{
			if (player_status[i]  && ((ny > py[i]) && (nx == px[i]))) // ���� �ذ�
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

void move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
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
	if (!placable(nx, ny)) {
		return;
	}


	move_tail(0, nx, ny);
}

void mugunghwa(void)
{
	mugunghwa_init();
	display();

	// ���� ���� Ÿ�̸�
	for (int i = DIALOG_DURATION_SEC; i > -1 ; i--)
	{
		dialog(0 , i);
	}
	
	while (1)
	{
		// ������ "����ȭ ���� �Ǿ����ϴ�" ���ϱ� �� ���� ��ȯ
		younghee();

		// ����� ������ Ű�Է�
		key_t key = get_key();
		if ((key == K_QUIT) || (n_alive == 1) || (count > 3) || (pass_n_player == n_alive))
		{
			break;
		}
		else if (key != K_UNDEFINED)
		{
			move_manual(key);
		}

		// �ٸ� NPC ���� ������ �۵�
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


	// ���� ��ġ
	for (int i = 0; i < 3; i++)
	{
		back_buf[6+i][1] = '#';
	}

	// n���� �÷��̾���� ���� ���� ������ ���� ��ġ
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
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
		for (int i = 0; i < 3; i++) // ���� '#'
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

		for (int i = 0; i < 3; i++) // ���� '@'
		{
			back_buf[6 + i][1] = '@';
		}
	}
	else if(tick > 9000) // �й��� ���
	{
		// Ż���� �˻�
		if (n_alivepost != n_alive)
		{
			n_alivepost = n_alive; // �������� ����ȭ

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

		for (int i = 0; i < 30; i++) // ����ȭ ��Ʈ �����
		{
			back_buf[15][i] = '.';
		}
		display();
		for (int i = 0; i < 30; i++)
		{
			back_buf[15][i] = ' ';
		}

		yh_killmode = false;
		tick = 0; // ƽ �ʱ�ȭ
		count++;
	}
}

void nightgame(void)
{

}

void juldarigi(void)
{

}

void jebi(void)
{

}

void nightgame_init(void)
{

}
void juldarigi_init(void)
{

}
void jebi_init(void)
{

}