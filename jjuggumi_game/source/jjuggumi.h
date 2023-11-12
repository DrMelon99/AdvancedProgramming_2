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

#define DIALOG_DURATION_SEC		4

bool player_status[PLAYER_MAX];  // �⺻�� true, Ż���ϸ� false
bool player_statuspost[PLAYER_MAX];

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // �÷��̾� ��, ��Ƴ��� �÷��̾� ��, ���� ������
int tick;  // �ð�
int pass_n_player;


int jjuggumi_init(void); // main() ���� �� �޲ٹ� ���� �÷��̾� ���� �Է� ����



// ===== ��Ÿ ��� =====
void intro(void); // [�޲ٹ� ���� ��Ʈ��] �Լ�
void ending(void);// [�޲ٹ� ���� ����] �Լ�
void sample(void); // [������ ���� ����] �Լ�

void move_random(int player, int dir);
void move_tail(int player, int nx, int ny);

#endif
