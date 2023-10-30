#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

void draw(void);
void print_status(void);

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col)
{
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col)
{
	gotoxy(row, col);
	printf("%c", ch);
}

// 두 버퍼를를 완전히 비우고 맵의 외곽을 #으로 구성
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

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
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

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void)
{
	draw();
	gotoxy(N_ROW + 3, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

// 
void draw(void) {
	for (int row = 0; row < N_ROW+1; row++) // 무궁화 꽃이 피었습니다 출력을 위해 임의로 N_ROW에 + 1
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
	char time_ment[] = "초 후 게임시작";
	char start_ment[] = "!!게 임 시 작 !!";
	char out_ment[] = "플레이어 탈락!";


	int Center_ROW = (N_ROW / 2) - 2;
	int Center_COL = ((N_COL -4) - 22) / 2;

	// '=' 다이얼 박스 생성
	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			back_buf[Center_ROW + j][Center_COL + i] = '=';
		}
	}
	
	// 다이얼 박스 공백 생성
	for (int i = 1; i < 32 ; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			back_buf[Center_ROW + j][Center_COL + i] = ' ';
		}
	}

	
	if (left_s > 0)
	{
		// 멘트 출력
		if (opt == 0) // 남은 초 멘트
		{
			for (int i = 0; i < 15; i++)
			{
				back_buf[Center_ROW + 2][Center_COL + 4] = left_s + 48; // 초 
				back_buf[Center_ROW + 2][Center_COL + 6 + i] = time_ment[i]; // + 멘트
			}
			display();
			Sleep(1000);
		}
		else if (opt == 1) // 탈락자 멘트
		{
			for (int i = 0; i < N_ROW; i++) // 화면 잠시 복사
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
						back_buf[Center_ROW + 2][Center_COL + 4 + j] = player_outlist[j] + 48; // 플레이어
					}
				}
				back_buf[Center_ROW + 2][Center_COL + 6 + n_player - n_alive + i] = out_ment[i]; // + 멘트
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

			for (int i = 0; i < N_ROW; i++) // 화면 복구
			{
				for (int j = 0; j < N_COL; j++)
				{
					back_buf[i][j] = temp_buf[i][j];
				}
			}
			display();
		}
	}
	else // 타이머 0
	{
		display();
		for (int i = 0; i < 16 ; i++)
		{
			back_buf[Center_ROW + 2][Center_COL + 5 + i] = start_ment[i]; // 게임 시작 멘트
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