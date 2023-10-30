#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#include "games.h"

#define PLAYER_MAX 10 // �ִ� �÷��̾� �� 10

#define DIALOG_DURATION_SEC		4

bool player_status[PLAYER_MAX];  // �⺻�� true, Ż���ϸ� false
bool player_statuspost[PLAYER_MAX];

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // �÷��̾� ��, ��Ƴ��� �÷��̾� ��, ���� ������
int tick;  // �ð�
int pass_n_player;

int randint(int low, int high); // low �̻� high ���� ������ �߻���Ű�� �Լ�
int jjuggumi_init(void); // main() ���� �� �޲ٹ� ���� �÷��̾� ���� �Է� ����

// ===== ��Ÿ ��� =====
void intro(void); // [�޲ٹ� ���� ��Ʈ��] �Լ�
void ending(void);// [�޲ٹ� ���� ����] �Լ�
void sample(void); // [������ ���� ����] �Լ�

#endif
