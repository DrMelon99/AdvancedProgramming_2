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
	intro(); // 쭈꾸미 게임 인트로
	mugunghwa(); // 무궁화 꽃이 피었습니다
	nightgame(); // 야간운동
	juldarigi(); // 줄다리기
	jebi(); // 제비 뽑기
	ending(); // 쭈꾸미 게임 엔딩

	return 0;
}

void jjuggumi_init(void)
{
	system_cursor();

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
	n_alive = n_player;

	// 파일에서 각 스탯 읽기
	for (int i = 0; i < n_player; i++)
	{
		PLAYER* p = &player[i];

		p->id = i;

		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name), &(p->intel), &(p->str));
		
		p->stamina = 100; // 스태미나 100%

		// 현재 상태
		p->is_alive[0] = p->is_alive[1] = true;
		p->hasitem = false;
	}

	// 아이템 데이터 load
	fscanf_s(fp, "%d", &n_item);

	for (int i = 0; i < n_item; i++)
	{
		item[i].id = i;
		item[i].getable = true;
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}
	fclose(fp);

	debug_toggle = false;

	tick[0] = 0;
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
		printf("====WINNER====");
		enline(3, 14);
		for (int i = 0; i < n_player; i++)
		{
			if (player[i].is_alive[0])
				printf("!!Player %d!! \n", i);
		}
		enline(2, 14);
	}
	else
	{
		printf("우승자를 가리지 못했습니다.\n");
		printf("===SURVIVOR LIST===");
		enline(1, 1);
		for (int i = 0; i < n_player; i++)
		{
			if (player[i].is_alive[0])
				printf("Player %d\n", i);
		}
		enline(2, 19);
	}
}

