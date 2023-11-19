#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

// �� (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col)
{
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �� row��, col���� ch ���
void printxy(char ch, int row, int col)
{
	gotoxy(row, col);
	printf("%c", ch);
}

// �� �� ���۸��� ������ ���� ���� �ܰ��� '*'�� ����
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

// �� back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
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

// �� ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void)
{
	draw();
	gotoxy(N_ROW + 1, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

// ���̾�α� ���
void draw(void)
{
	for (int row = 0; row < N_ROW; row++) // ����ȭ ���� �Ǿ����ϴ� ����� ���� ���Ƿ� N_ROW�� + 1
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

void print_status(void)
{
	printf("no. of players left: %2d\n", n_alive);
	enline(2,40);
	printf("\t\t intl\tstr\tstm\n");

	for (int p = 0; p < n_player; p++)
	{
		printf("player%2d: %s\t %d(+%d)\t%d(+%d)\t%d%%\n", p, player[p].is_alive ? "ALIVE" : "DEAD", player[p].intel, player[p].item.intel_buf, player[p].str, player[p].item.str_buf, player[p].stamina);
	}

	printf("Play time: %ds", tick/1000);
}

// �� ���� ���� temp ���ۿ� �ӽ� ����
void memory_front_buf(void)
{
	for (int i = 0; i < N_ROW; i++)
	{
		for (int j = 0; j < N_COL; j++)
		{
			temp_buf[i][j] = front_buf[i][j];
		}
	}
}

// �� �ֱٿ� �����ߴ� ���� back ���ۿ� ����
void restore_front_buf(void)
{
	for (int i = 0; i < N_ROW; i++)
	{
		for (int j = 0; j < N_COL; j++)
		{
			back_buf[i][j] = temp_buf[i][j];
		}
	}
}

void dialog(int opt)
{
	char time_ment[24] = "Game starts in n seconds"; // 'n' = 15
	char start_ment[16] = "!! GAME START !!";
	char out_ment[] = "PLAYER OUT !!";

	int Dialog_start_ROW;
	int Dialog_start_COL;

	memory_front_buf();

	if (opt == 0) // ī��Ʈ �ٿ� ���̾�α�
	{
		restore_front_buf();

		for (int t = 4; t > -2; t--)
		{
			Dialog_start_ROW = (N_ROW - 6) / 2;

			if (t > 0)
			{
				Dialog_start_COL = (N_COL / 2) - 13;

				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 28; j++)
					{
						back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = ' ';
						if (i == 0 || i == 4 || j == 0 || j == 27)
						{
							back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = '+';
						}
						else if (i == 2 && j > 1 && j < 26)
						{
							back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = time_ment[j - 2];
							back_buf[Dialog_start_ROW + i][Dialog_start_COL + 17] = '0' + t;
							if (t == 1 && j == 25)
							{
								back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = ' ';
							}
						}
					}
				}
				display();
				Sleep(1000);
			}
			else if (t == 0) // "GAME START" ���̾�α�
			{
				restore_front_buf();
				Dialog_start_COL = (N_COL / 2) - 9;

				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = ' ';
						if (i == 0 || i == 4 || j == 0 || j == 19)
						{
							back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = '+';
						}
						else if (i == 2 && j > 1 && j < 18)
						{
							back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = start_ment[j - 2];
						}
					}
				}
				display();
				Sleep(1000);
			}
			else
			{
				restore_front_buf();
				display();
			}
		}
	}
	else if (opt == 1) // Ż���� ��Ʈ ���̾�α�
	{

	}
	else if (opt == 2) // �߰���� ����
	{

	}

	//// '=' ���̾� �ڽ� ����
	//for (int i = 0; i < 33; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		back_buf[Center_ROW + j][Center_COL + i] = '=';
	//	}
	//}
	//
	//// ���̾� �ڽ� ���� ����
	//for (int i = 1; i < 32 ; i++)
	//{
	//	for (int j = 1; j < 4; j++)
	//	{
	//		back_buf[Center_ROW + j][Center_COL + i] = ' ';
	//	}
	//}

	//if (left_s > 0)
	//{
	//	// ��Ʈ ���
	//	if (opt == 0) // ���� �� ��Ʈ
	//	{
	//		for (int i = 0; i < 15; i++)
	//		{
	//			back_buf[Center_ROW + 2][Center_COL + 4] = left_s + 48; // �� 
	//			back_buf[Center_ROW + 2][Center_COL + 6 + i] = time_ment[i]; // + ��Ʈ
	//		}
	//		display();
	//		Sleep(1000);
	//	}
	//	else if (opt == 1) // Ż���� ��Ʈ
	//	{
	//		for (int i = 0; i < N_ROW; i++) // ȭ�� ��� ����
	//		{
	//			for (int j = 0; j < N_COL; j++)
	//			{
	//				temp_buf[i][j] = front_buf[i][j];
	//			}
	//		}

	//		for (int i = 0 ; i < 15; i++)
	//		{
	//			for (int j = 0 ; j < n_player - n_alive ; j++)
	//			{
	//				if (player_outlist[j] != 'v')
	//				{
	//					back_buf[Center_ROW + 2][Center_COL + 4 + j] = player_outlist[j] + 48; // �÷��̾�
	//				}
	//			}
	//			back_buf[Center_ROW + 2][Center_COL + 6 + n_player - n_alive + i] = out_ment[i]; // + ��Ʈ
	//		}
	//		display();
	//		Sleep(3000);

	//		for (int i = 0; i < 33; i++)
	//		{
	//			for (int j = 0; j < 5; j++)
	//			{
	//				back_buf[Center_ROW + j][Center_COL + i] = '.';
	//			}
	//		}
	//		display();
	//		for (int i = 0; i < 33; i++)
	//		{
	//			for (int j = 0; j < 5; j++)
	//			{
	//				back_buf[Center_ROW + j][Center_COL + i] = ' ';
	//			}
	//		}

	//		for (int i = 0; i < N_ROW; i++) // ȭ�� ����
	//		{
	//			for (int j = 0; j < N_COL; j++)
	//			{
	//				back_buf[i][j] = temp_buf[i][j];
	//			}
	//		}
	//		display();
	//	}
	//}
	//else // Ÿ�̸� 0
	//{
	//	display();
	//	for (int i = 0; i < 16 ; i++)
	//	{
	//		back_buf[Center_ROW + 2][Center_COL + 5 + i] = start_ment[i]; // ���� ���� ��Ʈ
	//	}

	//	display();
	//	Sleep(1000);

	//	for (int i = 0; i < 16; i++)
	//	{
	//		back_buf[Center_ROW + 2][Center_COL + 4 + i] = '.';
	//	}
	//	display();

	//	for (int i = 0; i < 33; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			back_buf[Center_ROW + j][Center_COL + i] = ' ';
	//		}
	//	}
	//	display();
	//}
}