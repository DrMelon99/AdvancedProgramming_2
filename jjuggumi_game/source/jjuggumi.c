// 2023-2 ������α׷��� ����: �޲ٹ� ���� // ����� ���� [������, ����ȣ ���ҹ�]
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
	intro(); // �޲ٹ� ���� ��Ʈ��
	mugunghwa(); // ����ȭ ���� �Ǿ����ϴ�
	nightgame(); // �߰��
	juldarigi(); // �ٴٸ���
	jebi(); // ���� �̱�
	ending(); // �޲ٹ� ���� ����

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
		printf("jjuggumi.dat���� ã�� �� ����\n���� ����");
		return -1;
	}

	fscanf_s(fp, "%d", &n_player);
	n_alive = n_player;

	// ���Ͽ��� �� ���� �б�
	for (int i = 0; i < n_player; i++)
	{
		PLAYER* p = &player[i];

		p->id = i;

		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name), &(p->intel), &(p->str));
		
		p->stamina = 100; // ���¹̳� 100%

		// ���� ����
		p->is_alive[0] = p->is_alive[1] = true;
		p->hasitem = false;
	}

	// ������ ������ load
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
	SetConsoleFontSize(10); // �ܼ� �۾� ũ�� ����
	system("mode con: cols=140 lines=165"); // �ܼ� â ũ�� ����

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
		printf("����ڸ� ������ ���߽��ϴ�.\n");
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

