// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임 // 살려조 팀원 [박제혁, 명지호 오소민]
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int main(void)
{
	jjuggumi_init();
	// intro(); // 쭈꾸미 게임 인트로
	mugunghwa(); // 무궁화 꽃이 피었습니다
	// nightgame(); // 야간운동
	// juldarigi(); // 줄다리기
	// jebi(); // 제비 뽑기
	// sample();
	// ending(); // 쭈꾸미 게임 엔딩

	return 0;
}

int jjuggumi_init(void)
{
	char start_option;

	SetConsoleFontSize(14);
	system("mode con: cols=50 lines=80");

	srand((unsigned int)time(NULL));

	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");

	if (fp == NULL)
	{
		printf("jjuggumi.dat파일 찾을 수 없음\n게임 종료");
		return -1;
	}

	fscanf_s(fp, "%d", &n_player);

	// 파일에서 각 스탯 읽기
	for (int i = 0; i < n_player; i++)
	{
		PLAYER* p = &player[i];

		p->id = i;

		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name), &(p->intel), &(p->str));
		
		p->stamina = 100; // 스태미나 100%

		// 현재 상태
		p->is_alive = true;
		p->hasitem = false;

		/*if (i == 0)
		{
			do
			{
				printf("0번째 플레이어인 당신은 %s(이)가 맞습니까?\n(y / n) >> ", p->name);
				scanf_s(" %c", &start_option, 1);

				if (start_option == 'n')
				{
					printf("0번째 플레이어 이름 편집\n");
					printf("이름>> ");
					scanf_s(" %s", &p->name, 50);
				}


			} while ((start_option != 'y'));
		}*/
	}

	// 아이템 데이터 load
	fscanf_s(fp, "%d", &n_item);
	for (int i = 0; i < n_item; i++) {
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}
	fclose(fp);

	/*for (int i = 0; i < n_player; i++)
	{
		printf("번호: %d\n이름: %s\n지능: %d\n힘: %d\n스태미나:%d\n생존여부: %d\n\n", player[i].id, player[i].name, player[i].intel, player[i].str, player[i].stamina, player[i].is_alive);
	}*/

	/*for (int i = 0; i < n_item; i++)
	{
		printf("아이템 이름: %s\n지능 버프: %d\n힘 버프: %d\n스태미나 버프: %d\n\n", item[i].name, item[i].intel_buf, item[i].str_buf, item[i].stamina_buf);
	}*/
	

	//do
	//{
	//	printf("플레이어 수 (1~10): ");
	//	scanf_s("%d", &n_player); // 플레이어 수 입력 받기

	//} while (n_player < 2 || n_player > 10);
	//

	//n_alive = n_alivepost = n_player; // 살아남은 플레이어 수를 입력받은 플레이어 수로 초기화

	//for (int i = 0; i < n_player; i++)
	//{
	//	player_status[i] = player_statuspost[i] = true;
	//} // 입력받은 n명의 플레이어들을 모두 true(살아있음)로 지정

	tick = 0;

	/*system("cls");*/

	return 0;
}

void intro(void)
{
	SetConsoleFontSize(10); // 콘솔 글씨 크기 변경
	system("mode con: cols=140 lines=165"); // 콘솔 창 크기 조정

	enline(2, 140);
	titlesong();
	system("cls");
}

void ending(void)
{
	system("cls");

	if (n_alive == 1)
	{
		printf("최종 우승자");
		enline(3, 15);
		for (int i = 0; i < n_player; i++)
		{
			if (player_status[i])
			{
				printf("%d번 플레이어\n", i);
			}
		}
		enline(2, 15);
	}
	else
	{
		printf("생존자 목록");
		enline(3, 15);
		for (int i = 0; i < n_player; i++)
		{
			if (player_status[i])
			{
				printf("%d번 플레이어\n", i);
			}
		}
		enline(2, 15);
	}
}

