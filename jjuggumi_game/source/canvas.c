#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col)
{
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col)
{
	gotoxy(row, col);
	printf("%c", ch);
}

// �� ���۸��� ������ ���� ���� �ܰ��� #���� ����
void map_init(int n_row, int n_col)
{
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;

	for (int i = 0; i < N_ROW; i++)
	{
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++)
		{
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col)
{
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ')
	{
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void)
{
	draw();
	gotoxy(N_ROW + 3, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

// 
void draw(void) {
	for (int row = 0; row < N_ROW+1; row++) // ����ȭ ���� �Ǿ����ϴ� ����� ���� ���Ƿ� N_ROW�� + 1
	{
		for (int col = 0; col < N_COL; col++)
		{
			if (front_buf[row][col] != back_buf[row][col])
			{
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %2d\n", n_alive);
	for (int p = 0; p < n_player; p++)
	{
		printf("player %2d: %5s\n", p, player_status[p] ? "alive" : "DEAD");
	}
}

void dialog(int opt, int left_s)
{
	char time_ment[] = "�� �� ���ӽ���";
	char start_ment[] = "!!�� �� �� �� !!";
	char out_ment[] = "�÷��̾� Ż��!";


	int Center_ROW = (N_ROW / 2) - 2;
	int Center_COL = ((N_COL -4) - 22) / 2;

	// '=' ���̾� �ڽ� ����
	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			back_buf[Center_ROW + j][Center_COL + i] = '=';
		}
	}
	
	// ���̾� �ڽ� ���� ����
	for (int i = 1; i < 32 ; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			back_buf[Center_ROW + j][Center_COL + i] = ' ';
		}
	}

	
	if (left_s > 0)
	{
		// ��Ʈ ���
		if (opt == 0) // ���� �� ��Ʈ
		{
			for (int i = 0; i < 15; i++)
			{
				back_buf[Center_ROW + 2][Center_COL + 4] = left_s + 48; // �� 
				back_buf[Center_ROW + 2][Center_COL + 6 + i] = time_ment[i]; // + ��Ʈ
			}
			display();
			Sleep(1000);
		}
		else if (opt == 1) // Ż���� ��Ʈ
		{
			for (int i = 0; i < N_ROW; i++) // ȭ�� ��� ����
			{
				for (int j = 0; j < N_COL; j++)
				{
					temp_buf[i][j] = front_buf[i][j];
				}
			}

			for (int i = 0 ; i < 15; i++)
			{
				for (int j = 0 ; j < n_player - n_alive ; j++)
				{
					if (player_outlist[j] != 'v')
					{
						back_buf[Center_ROW + 2][Center_COL + 4 + j] = player_outlist[j] + 48; // �÷��̾�
					}
				}
				back_buf[Center_ROW + 2][Center_COL + 6 + n_player - n_alive + i] = out_ment[i]; // + ��Ʈ
			}
			display();
			Sleep(3000);

			for (int i = 0; i < 33; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					back_buf[Center_ROW + j][Center_COL + i] = '.';
				}
			}
			display();
			for (int i = 0; i < 33; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					back_buf[Center_ROW + j][Center_COL + i] = ' ';
				}
			}

			for (int i = 0; i < N_ROW; i++) // ȭ�� ����
			{
				for (int j = 0; j < N_COL; j++)
				{
					back_buf[i][j] = temp_buf[i][j];
				}
			}
			display();
		}
	}
	else // Ÿ�̸� 0
	{
		display();
		for (int i = 0; i < 16 ; i++)
		{
			back_buf[Center_ROW + 2][Center_COL + 5 + i] = start_ment[i]; // ���� ���� ��Ʈ
		}

		display();
		Sleep(1000);

		for (int i = 0; i < 16; i++)
		{
			back_buf[Center_ROW + 2][Center_COL + 4 + i] = '.';
		}
		display();

		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				back_buf[Center_ROW + j][Center_COL + i] = ' ';
			}
		}
		display();
	}
}