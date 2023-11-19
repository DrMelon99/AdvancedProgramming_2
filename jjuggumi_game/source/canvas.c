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

// 다이얼로그 출력
void draw(void)
{
	for (int row = 0; row < N_ROW; row++) // 무궁화 꽃이 피었습니다 출력을 위해 임의로 N_ROW에 + 1
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

// ★ 현재 맵을 temp 버퍼에 임시 저장
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

void dialog(int opt)
{
	char time_ment[24] = "Game starts in n seconds"; // 'n' = 15
	char start_ment[16] = "!! GAME START !!";
	char out_ment[] = "PLAYER OUT !!";

	int Dialog_start_ROW;
	int Dialog_start_COL;

	memory_front_buf();

	if (opt == 0) // 카운트 다운 다이얼로그
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
	}
	else if (opt == 1) // 탈락자 멘트 다이얼로그
	{

	}
	else if (opt == 2) // 추가기능 예정
	{

	}

	//// '=' 다이얼 박스 생성
	//for (int i = 0; i < 33; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		back_buf[Center_ROW + j][Center_COL + i] = '=';
	//	}
	//}
	//
	//// 다이얼 박스 공백 생성
	//for (int i = 1; i < 32 ; i++)
	//{
	//	for (int j = 1; j < 4; j++)
	//	{
	//		back_buf[Center_ROW + j][Center_COL + i] = ' ';
	//	}
	//}

	//if (left_s > 0)
	//{
	//	// 멘트 출력
	//	if (opt == 0) // 남은 초 멘트
	//	{
	//		for (int i = 0; i < 15; i++)
	//		{
	//			back_buf[Center_ROW + 2][Center_COL + 4] = left_s + 48; // 초 
	//			back_buf[Center_ROW + 2][Center_COL + 6 + i] = time_ment[i]; // + 멘트
	//		}
	//		display();
	//		Sleep(1000);
	//	}
	//	else if (opt == 1) // 탈락자 멘트
	//	{
	//		for (int i = 0; i < N_ROW; i++) // 화면 잠시 복사
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
	//					back_buf[Center_ROW + 2][Center_COL + 4 + j] = player_outlist[j] + 48; // 플레이어
	//				}
	//			}
	//			back_buf[Center_ROW + 2][Center_COL + 6 + n_player - n_alive + i] = out_ment[i]; // + 멘트
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

	//		for (int i = 0; i < N_ROW; i++) // 화면 복구
	//		{
	//			for (int j = 0; j < N_COL; j++)
	//			{
	//				back_buf[i][j] = temp_buf[i][j];
	//			}
	//		}
	//		display();
	//	}
	//}
	//else // 타이머 0
	//{
	//	display();
	//	for (int i = 0; i < 16 ; i++)
	//	{
	//		back_buf[Center_ROW + 2][Center_COL + 5 + i] = start_ment[i]; // 게임 시작 멘트
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