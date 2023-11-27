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

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // �÷��̾� ��, ��Ƴ��� �÷��̾� ��, ���� ������
int n_item;
int game_round; // ���� ���� ���� ��
int debug_i, debug_j, debug_k; // ����� ���� ����

int tick[2];  // �ð�

int pass_n_player;

typedef struct {
	int id;
	char name[100]; // ������ �̸�
	bool getable; // ������ ���� ���� ����
	int ix, iy; // ������ ��ǥ x,y
	int intel_buf, str_buf, stamina_buf; // �������� ����, ��, ���¹̳� ���� �ɷ�ġ
} ITEM;

ITEM item[ITEM_MAX]; // ITEM �迭 �ε����� �ִ�ġ�� ITEM_MAX�� ����

typedef struct {
	int id; // �÷��̾� ��ȣ
	int px, py; // �÷��̾� ��ǥ x,y
	int period; // �÷��̾� �̵��ֱ�
	char name[100]; // �÷��̾� �̸�
	int intel, str, stamina; // �÷��̾� ����, ��, ���¹̳�
	bool is_alive[2]; // �÷��̾� ���� ���� 0: ����, 1: ���� ǥ�� ���� ��
	bool hasitem, is_pass; // ������ ��������, ������� ����
	int interact_timestamp; // ��ȣ�ۿ� ��Ÿ��
	ITEM item; // �÷��̾ ������ �ִ� ������ ����
} PLAYER;

PLAYER player[PLAYER_MAX]; // �÷��̾� �迭 �ε����� �ִ�ġ�� PLAYER_MAX�� ����

// main() ���� �� �޲ٹ� ���� �÷��̾� ���� �Է� ����
int jjuggumi_init(void);
// [�޲ٹ� ���� ��Ʈ��] �Լ�
void intro(void);
// [�޲ٹ� ���� ����] �Լ�
void ending(void);
// [������ ���� ����] �Լ�
void sample(void);

#endif
