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

// �������� �ִ� �� ��ǥ�� ���
void draw(void)
{
	for (int row = 0; row < N_ROW + 1; row++) // ����ȭ ���� �Ǿ����ϴ� ����� ���� ���Ƿ� N_ROW�� + 1
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

// ���� ���
void print_status(void)
{
	printf("no. of players left: %2d\n", n_alive);
	enline(2,40);
	printf("\t\t intl\tstr\tstm\n");

	for (int p = 0; p < n_player; p++)
	{
		printf("player%2d: %s\t %2d(%+2d)\t%2d(%+2d)\t%3d%%\titem :%d [%d]\n", p, player[p].is_alive ? "ALIVE" : "DEAD", player[p].intel, player[p].item.intel_buf, player[p].str, player[p].item.str_buf, player[p].stamina, player[p].hasitem, player[p].item.id);
	}

	for (int i = 0; i < n_item; i++) // ����� â
	{
		printf("Item id: %d\tGetable: %d\tX: %02d\tY: %02d\n", item[i].id, item[i].getable, item[i].ix, item[i].iy);
	}

	printf("Play time: %03ds", tick[0] / 1000);
	printf("\nX:%02d Y:%02d", player[0].px, player[0].py);
}

// �� ���� ���� temp ���ۿ� �ӽ� ����
void memory_front_buf(void)
{
	for (int i = 0; i < N_ROW; i++)
	{
		for (int j = 0; j < N_COL; j++)
		{
			temp_buf[i][j] = back_buf[i][j];
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

// �� ���̾�α� ���
void dialog(int opt)
{
	char time_ment[24] = "Game starts in n seconds"; // 'n' = 15
	char start_ment[16] = "!! GAME START !!";
	char out_ment[16] = "!! PLAYER OUT !!";
	char item_exchange[26] = "Want to exchange an item??";
	char select_ment[17] = "(SPACE to Select)";
	char fight[30] = "Do you want to fight Player n?";

	int Dialog_start_ROW;
	int Dialog_start_COL;

	memory_front_buf();

	
	if (opt == 0) // ī��Ʈ �ٿ� ���̾�α�
	{
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
		restore_front_buf();
	}
	else if (opt == 1) // "����ȭ ���� �Ǿ����ϴ�" Ż���� ��Ʈ ���̾�α�
	{

	}
	else if (opt == 2) // "�߰��" 0�� �÷��̾�, ������ ���� ����
	{
		Dialog_start_ROW = (N_ROW - 8) / 2;
		Dialog_start_COL = (N_COL / 2) - 14;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = ' ';
				if (i == 0 || i == 8 || j == 0 || j == 29)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = '+';
				}
				else if (i == 2 && j > 1 && j < 28)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = item_exchange[j - 2];
				}
				else if (i == 3 && j > 5 && j < 23)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = select_ment[j - 6];
				}
				back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 8] = 'Y';
				back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 21] = 'N';
			}
		}

		get_item = true;

		while (1)
		{
			key_t key = get_key();

			if (key == K_LEFT)
			{
				get_item = true;
			}
			else if (key == K_RIGHT)
			{
				get_item = false;
			}
			else if (key == K_SPACE)
			{
				break;
			}
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 8] = ' ';
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 21] = ' ';

			if (get_item)
			{
				back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 8] = '^';
			}
			else
			{
				back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 21] = '^';
			}
			display();
			Sleep(10);
		}
		restore_front_buf();
		display();
	}
	else if (opt == 3) // "�߰��" 0�� �÷��̾�, �ٸ� �÷��̾�� ����ĭ ��ȣ�ۿ� 
	{
		// <��Ż / ȸ�� / ����>
	}
}