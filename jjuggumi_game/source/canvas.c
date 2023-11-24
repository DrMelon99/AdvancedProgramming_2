#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

// ★ (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col)
{
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ★ row행, col열에 ch 출력
void printxy(char ch, int row, int col)
{
	gotoxy(row, col);
	printf("%c", ch);
}

// ★ 두 버퍼를를 완전히 비우고 맵의 외곽을 '*'로 구성
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

// ★ back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
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

// ★ 상단에 맵을, 하단에는 현재 상태를 출력
void display(void)
{
	draw();
	gotoxy(N_ROW + 1, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

// 변경점이 있는 맵 좌표에 출력
void draw(void)
{
	for (int row = 0; row < N_ROW + 1; row++) // 무궁화 꽃이 피었습니다 출력을 위해 임의로 N_ROW에 + 1
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

// 상태 출력
void print_status(void)
{	
	printf("no. of players left: %2d\n", n_alive);
	enline(2,40);
	printf("\t\t intl\tstr\tstm\n");

	for (int p = 0; p < n_player; p++)
	{
		printf("player%2d: %s\t %2d(%+2d)\t%2d(%+2d)\t%3d%%\titem :%d [%d]\n", p, player[p].is_alive ? "ALIVE" : "DEAD", player[p].intel, player[p].item.intel_buf, player[p].str, player[p].item.str_buf, player[p].stamina, player[p].hasitem, player[p].item.id);
	}

	debug();
}

// ★ 현재 맵을 temp 버퍼에 임시 저장
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

// ★ 최근에 저장했던 맵을 back 버퍼에 복원
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

// ♨ 다이얼로그 출력
void dialog(int opt, int data)
{
	char time_ment[24] = "Game starts in n seconds"; // 'n' = 15
	char start_ment[16] = "!! GAME START !!";
	char out_ment[16] = "!! PLAYER OUT !!";
	char item_exchange[26] = "Want to exchange an item??";
	char select_ment[17] = "(SPACE to Select)";
	char fight_ment[30] = "Do you want to fight Player n?";
	char fight_opt[3][10] = { "Force", "Intercept", "Ignor" };

	int Dialog_start_ROW;
	int Dialog_start_COL;

	memory_front_buf();

	
	if (opt == 0) // 카운트 다운 다이얼로그
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
			else if (t == 0) // "GAME START" 다이얼로그
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
	else if (opt == 1) // "무궁화 꽃이 피었습니다" 탈락자 멘트 다이얼로그
	{

	}
	else if (opt == 2) // "야간운동" 0번 플레이어, 아이템 습득 여부
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
	else if (opt == 3) // "야간운동" 0번 플레이어, 다른 플레이어와 인접칸 상호작용 
	{
		Dialog_start_ROW = (N_ROW - 10) / 2;
		Dialog_start_COL = (N_COL / 2) - 16;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 34; j++)
			{
				back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = ' ';
				if (i == 0 || i == 9 || j == 0 || j == 33)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = '+';
				}
				else if (i == 2 && j > 1 && j < 32)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = fight_ment[j - 2];
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + 30] = '0' + data;
				}
				else if (i == 3 && j > 8 && j < 26)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = select_ment[j - 9];
				}
				else if (i == 5 && j > 13 && j < 19)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = fight_opt[0][j - 14];
				}
				else if (i == 6 && j > 11 && j < 21)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = fight_opt[1][j - 12];
				}
				else if (i == 7 && j > 13 && j < 19)
				{
					back_buf[Dialog_start_ROW + i][Dialog_start_COL + j] = fight_opt[2][j - 14];
				}
			}
		}

		fight = 0;

		// <강탈 / 회유 / 무시>
		while (1)
		{
			if (fight < 0) { fight = 0; }
			if (fight > 2) { fight = 2; }

			back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 12] = ' ';
			back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 20] = ' ';
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 10] = ' ';
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 22] = ' ';
			back_buf[Dialog_start_ROW + 7][Dialog_start_COL + 12] = ' ';
			back_buf[Dialog_start_ROW + 7][Dialog_start_COL + 20] = ' ';

			if (fight == 0)
			{
				back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 12] = '>';
				back_buf[Dialog_start_ROW + 5][Dialog_start_COL + 20] = '<';
			}
			else if (fight == 1)
			{
				back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 10] = '>';
				back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 22] = '<';
			}
			else
			{
				back_buf[Dialog_start_ROW + 7][Dialog_start_COL + 12] = '>';
				back_buf[Dialog_start_ROW + 7][Dialog_start_COL + 20] = '<';
			}

			key_t key = get_key();

			if (key == K_UP)
			{
				fight --;
			}
			else if (key == K_DOWN)
			{
				fight ++;
			}
			else if (key == K_SPACE)
			{
				break;
			}
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 8] = ' ';
			back_buf[Dialog_start_ROW + 6][Dialog_start_COL + 21] = ' ';

			display();
			Sleep(10);
		}
		restore_front_buf();
		display();
	}
}

void debug(void)
{
	for (int i = 0; i < n_item; i++)
	{
		printf("Item id: %d Getable: %d X: %02d Y: %02d\n", item[i].id, item[i].getable, item[i].ix, item[i].iy);
	}

	printf("Play time: %03ds\n", tick[0] / 1000);
	printf("Player Location -> X:%02d Y:%02d\n", player[0].px, player[0].py);
	printf("fight: %d", fight);
}