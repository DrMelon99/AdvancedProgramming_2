#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>

#include "jjuggumi.h"
#include "canvas.h"
#include "games.h"

#define PLAYER_MAX 10 // �ִ� �÷��̾� �� 10
#define ITEM_MAX 10

#define DIALOG_DURATION_SEC	4

bool player_statuspost[PLAYER_MAX];

// int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // �÷��̾� ��, ��Ƴ��� �÷��̾� ��, ���� ������
int n_item;

int tick;  // �ð�
int pass_n_player;

typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
} ITEM;

ITEM item[ITEM_MAX];

typedef struct {
	int id;
	int px, py;
	int period;
	char name[100];
	int intel, str, stamina;
	bool is_alive, hasitem;
	ITEM item;
} PLAYER;

PLAYER player[PLAYER_MAX];

// main() ���� �� �޲ٹ� ���� �÷��̾� ���� �Է� ����
int jjuggumi_init(void);
// [�޲ٹ� ���� ��Ʈ��] �Լ�
void intro(void);
// [�޲ٹ� ���� ����] �Լ�
void ending(void);
// [������ ���� ����] �Լ�
void sample(void);

#endif
