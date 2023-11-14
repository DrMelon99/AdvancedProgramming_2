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
	// intro(); // �޲ٹ� ���� ��Ʈ��
	mugunghwa(); // ����ȭ ���� �Ǿ����ϴ�
	// nightgame(); // �߰��
	// juldarigi(); // �ٴٸ���
	// jebi(); // ���� �̱�
	// sample();
	// ending(); // �޲ٹ� ���� ����

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
		printf("jjuggumi.dat���� ã�� �� ����\n���� ����");
		return -1;
	}

	fscanf_s(fp, "%d", &n_player);

	// ���Ͽ��� �� ���� �б�
	for (int i = 0; i < n_player; i++)
	{
		PLAYER* p = &player[i];

		p->id = i;

		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name), &(p->intel), &(p->str));
		
		p->stamina = 100; // ���¹̳� 100%

		// ���� ����
		p->is_alive = true;
		p->hasitem = false;

		/*if (i == 0)
		{
			do
			{
				printf("0��° �÷��̾��� ����� %s(��)�� �½��ϱ�?\n(y / n) >> ", p->name);
				scanf_s(" %c", &start_option, 1);

				if (start_option == 'n')
				{
					printf("0��° �÷��̾� �̸� ����\n");
					printf("�̸�>> ");
					scanf_s(" %s", &p->name, 50);
				}


			} while ((start_option != 'y'));
		}*/
	}

	// ������ ������ load
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
		printf("��ȣ: %d\n�̸�: %s\n����: %d\n��: %d\n���¹̳�:%d\n��������: %d\n\n", player[i].id, player[i].name, player[i].intel, player[i].str, player[i].stamina, player[i].is_alive);
	}*/

	/*for (int i = 0; i < n_item; i++)
	{
		printf("������ �̸�: %s\n���� ����: %d\n�� ����: %d\n���¹̳� ����: %d\n\n", item[i].name, item[i].intel_buf, item[i].str_buf, item[i].stamina_buf);
	}*/
	

	//do
	//{
	//	printf("�÷��̾� �� (1~10): ");
	//	scanf_s("%d", &n_player); // �÷��̾� �� �Է� �ޱ�

	//} while (n_player < 2 || n_player > 10);
	//

	//n_alive = n_alivepost = n_player; // ��Ƴ��� �÷��̾� ���� �Է¹��� �÷��̾� ���� �ʱ�ȭ

	//for (int i = 0; i < n_player; i++)
	//{
	//	player_status[i] = player_statuspost[i] = true;
	//} // �Է¹��� n���� �÷��̾���� ��� true(�������)�� ����

	tick = 0;

	/*system("cls");*/

	return 0;
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
		printf("���� �����");
		enline(3, 15);
		for (int i = 0; i < n_player; i++)
		{
			if (player_status[i])
			{
				printf("%d�� �÷��̾�\n", i);
			}
		}
		enline(2, 15);
	}
	else
	{
		printf("������ ���");
		enline(3, 15);
		for (int i = 0; i < n_player; i++)
		{
			if (player_status[i])
			{
				printf("%d�� �÷��̾�\n", i);
			}
		}
		enline(2, 15);
	}
}

