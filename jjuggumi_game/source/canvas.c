#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

void display(void)
{
	draw();
	gotoxy(N_ROW + 2, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

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

void printxy(char ch, int row, int col)
{
	gotoxy(row, col);
	printf("%c", ch);
}

void gotoxy(int row, int col)
{
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_status(void)
{
	if (game_round == 1) // "무궁화 꽃이 피었습니다"
	{
		enline(2, 60);
		printf("no. of Players left: %2d", n_alive);
		enline(1, 60);
		for (int p = 0; p < n_player; p++)
		{
			printf("Player%2d: %s\n", p, player[p].is_alive[0] ? "ALIVE" : "DEAD");
		}
	}
	else if (game_round == 2) // "야간게임"
	{
		enline(2, 80);
		printf("no. of Players left: %2d", n_alive);
		enline(3, 80);
		printf("\t\t intl\tstr\tstm\n");
		for (int p = 0; p < n_player; p++)
		{
			printf("Player%2d: %s\t %2d(%+2d)\t%2d(%+2d)\t%3d%%", p, player[p].is_alive[0] ? "ALIVE" : "DEAD ", player[p].intel, player[p].item.intel_buf, player[p].str, player[p].item.str_buf, player[p].stamina);
			// printf("\thas item :%s, item id: [%d], period: %03d", player[p].hasitem ? "YES" : "NO ", player[p].item.id, player[p].period);
			printf("\n");
		}
	}
	else if (game_round == 3) // "줄다리기"
	{
		enline(2, 32);
		printf("str:\t%+d", 0);
		enline(1, -1);
		printf("no. of Players left: %2d", n_alive);
		enline(3, 32);
		for (int p = 0; p < n_player; p++)
		{
			printf("Player%2d: %s\n", p, player[p].is_alive[0] ? "ALIVE" : "ALIVE*");
		}
	}
	else if (game_round == 4) // "제비뽑기"
	{
		enline(2, 34);
		printf("[Round %d] Turn: Player %d\n", count, ingame_exchange_data);
	}

	// debug();
}

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

void print_addi_status(int opt, int p1, int p2)
{
	if (opt == 0) // 비우기
	{
		for (int i = 0; i < N_COL; i++)
		{
			back_buf[N_ROW][i] = ' ';
		}
	}
	else if (opt == 1)
	{
		for (int i = 0; i < 13; i++)
		{
			if (i == 7)
			{
				back_buf[N_ROW][i] = '0' + p1;
			}
			else
			{
				back_buf[N_ROW][i] = DIE_MESSAGE[i];
			}
		}
	}
	else if (opt == 2) // "무궁화 꽃이 피었습니다"
	{
		/*여기에 이전 younghee의 코드 내용을 리팩토링 후 옮길 것*/
	}
	else if (opt == 3)
	{
		for (int i = 0; i < 25; i++)
		{
			if (i == 7)
			{
				back_buf[N_ROW][i] = '0' + p1;
			}
			else
			{
				back_buf[N_ROW][i] = NIGHTGAME_ALART1[i];
			}
		}
	}
	else if (opt == 4)
	{
		for (int i = 0; i < 37; i++)
		{
			if (i == 7)
			{
				back_buf[N_ROW][i] = '0' + p1;
			}
			else if (i == 36)
			{
				back_buf[N_ROW][i] = '0' + p2;
			}
			else
			{
				back_buf[N_ROW][i] = NIGHTGAME_ALART2[i];
			}
		}
	}
	
}

void dialog(int opt, int data)
{
	char time_ment[24] = "Game starts in n seconds"; // 게임 시작 타이머
	char start_ment[16] = "!! GAME START !!"; // 게임 시작 타이머 0초
	char out_ment[13] = "PLAYER OUT !!"; // "무궁화 꽃이 피었습나다" 전용 탈락 화면
	char item_exchange[26] = "Want to exchange an item??";
	char select_ment[17] = "(SPACE to Select)";
	char fight_ment[30] = "Do you want to fight Player n?";
	char fight_opt[3][10] = { "Force", "Intercept", "Ignor" };

	int Dialog_start_ROW;
	int Dialog_start_COL;

	memory_front_buf();

	if (opt == 0) // 카운트 다운 다이얼로그
	{	
		for (int t = 3; t > -2; t--)
		{
			Dialog_start_ROW = (N_ROW - 5) / 2;

			if (t > 0)
			{
				Dialog_start_COL = (N_COL / 2) - 14;

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
				Beep(SOUND_C / 2, 100);
				Sleep(900);
			}
			else if (t == 0) // "GAME START" 다이얼로그
			{
				restore_front_buf();
				Dialog_start_COL = (N_COL / 2) - 10;

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
				Beep(SOUND_C, 100);
				Sleep(900);
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
	else if (opt == 2) // "야간운동" 0번 플레이어, 아이템 습득 여부 선택 다이얼로그
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

			key_t key = get_key();

			if ((key == K_LEFT) || (key == K_RIGHT))
			{
				Beep(SOUND_D, 5);
				get_item = !get_item;
			}
			else if (key == K_SPACE)
			{
				Beep(SOUND_D * 2, 5);
				break;
			}

			display();
			Sleep(10);
		}
		restore_front_buf();
		display();
	}
	else if (opt == 3) // "야간운동" 0번 플레이어, 인접한 다른 플레이어와 상호작용 여부 선택 다이얼로그
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

		// <강탈: Force / 회유: Intercept / 무시: Ignor>
		while (1)
		{
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
				Beep(SOUND_D, 5);
				if (fight == 0)
				{
					fight = 2;
				}
				else
				{
					fight--;
				}
			}
			else if (key == K_DOWN)
			{
				Beep(SOUND_D, 5);
				if (fight == 2)
				{
					fight = 0;
				}
				else
				{
					fight++;
				}
			}
			else if (key == K_SPACE)
			{
				Beep(SOUND_D * 2, 5);
				break;
			}

			display();
			Sleep(10);
		}
		restore_front_buf();
		display();
	}
	else if (opt == 4) // "제비뽑기" n번째 플레이어의 <통과> 판정 결과 출력 다이얼로그
	{
		char jb_pment[14] = "Player n pass!";

		Dialog_start_ROW = 3;
		Dialog_start_COL = 1;
		for (int i = 0; i < 28; i++) {
			back_buf[Dialog_start_COL][Dialog_start_ROW + i] = '+';
			back_buf[Dialog_start_COL + 1][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 3][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 4][Dialog_start_ROW + i] = '+';
		}
		for (int i = 0; i < 5; i++) {
			back_buf[Dialog_start_COL + i][Dialog_start_ROW] = '+';
			back_buf[Dialog_start_COL + i][Dialog_start_ROW +27] = '+';
		}
		for (int i = 0; i < 14; i++) {
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + 7 + i] = jb_pment[i];
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + 7 + 7] = '0' + data;
		}

		display();
		Sleep(1000);
		restore_front_buf();
	}
	else if (opt == 5) // "제비뽑기" n번째 플레이어의 <탈락> 판정 결과 출력 다이얼로그
	{
		char jb_fment[14] = "Player n fail!";

		Dialog_start_ROW = 3;
		Dialog_start_COL = 1;
		for (int i = 0; i < 28; i++) {
			back_buf[Dialog_start_COL][Dialog_start_ROW + i] = '+';
			back_buf[Dialog_start_COL + 1][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 3][Dialog_start_ROW + i] = ' ';
			back_buf[Dialog_start_COL + 4][Dialog_start_ROW + i] = '+';
		}
		for (int i = 0; i < 5; i++) {
			back_buf[Dialog_start_COL + i][Dialog_start_ROW] = '+';
			back_buf[Dialog_start_COL + i][Dialog_start_ROW + 27] = '+';
		}
		for (int i = 0; i < 14; i++) {
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + 7 + i] = jb_fment[i];
			back_buf[Dialog_start_COL + 2][Dialog_start_ROW + 7 + 7] = '0' + data;
		}

		display();
		Sleep(1000);
		restore_front_buf();
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
	printf("get item: %d fight: %d", get_item, fight);
}