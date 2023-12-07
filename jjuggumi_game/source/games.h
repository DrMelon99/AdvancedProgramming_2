#ifndef _GAMES_H_
#define _GAMES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "jjuggumi.h"
#include "keyin.h"
#include "canvas.h"
#include "miscellaneous.h"

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

#define DIE_MESSAGE "Player n died"
#define MUGUNWHA_MENT "�� �� ȭ �� �� �� �� �� �� ��"
#define NIGHTGAME_ALART1 "Player n obtained an item"
#define NIGHTGAME_ALART2 "Player n steals an item from Player n"

bool yh_killmode, get_item;
int fight;
int count;
int x, y;
int ingame_exchange_data;

int picked_jb, unpicked_jb;
int jb_pf[10]; // ���� ��÷ ����
int pl_cnt, r1; // �÷��̾�, ���� 1
int jb_num;
int pl_now[10];
int jb_cnt, p_cnt;

/* ���� ���� */
// �� ����� ������ ����
bool player_control(void);
// �� NPC ������ ����
void move_random(int player, int dir);
// �� back_buf[][]�� ������ �ݿ�
void move_tail(int player, int nx, int ny);
// �� ���� �÷��̾� �ð�ȭ
void player_visable(void);
// �� �÷��̾� ���¹̳� ����
void player_stamina(int p, int opt, int stamina_val);

/* "����ȭ ���� �Ǿ����ϴ�" ���� */
// �� "����ȭ ���� �Ǿ����ϴ�" ����
void mugunghwa(void);
// �� "����ȭ ���� �Ǿ����ϴ�" �ʱ� ����
void mugunghwa_init(void);
// �� "����ȭ ���� �Ǿ����ϴ�" NPC ������ ����
void npc_move_mugunghwa(void);
// �� "����ȭ ���� �Ǿ����ϴ�" back_buf[][]�� ������ �ݿ�
void move_tail_mugunghwa(int player, int nx, int ny);
// �� "����ȭ ���� �Ǿ����ϴ�" ���� �ൿ ����
void younghee(void);

/* "�߰��" ���� */
// �� "�߰��" ����
void nightgame(void);
// �� "�߰��" �ʱ� ����
void nightgame_init(void);
// �� "�߰��" NPC ������ ����
void npc_move_nightgame(void);
// �� "�߰��" ������ �ð�ȭ
void nightgame_item_visable(void);

/* "�ٴٸ���" ���� */
// �� "�ٴٸ���" ����
void juldarigi(void);
// �� "�ٴٸ���" �ʱ� ����
void juldarigi_init(void);
// �� "�ٴٸ���" ���� ȭ�� - ���� ���� ��(����) 
void map_init_juldarigi(int n_row, int n_col);

/* "����̱�" ���� */
// �� "����̱�" ����
void jebi(void);
// �� "����̱�" �ʱ� ����
void jebi_init(void);
//���� ����
void jebi_mix(int[]);
//���� ���� ���� ���ϱ�
void player_mix(int[]);
//���� �̱� ����
bool pick_jebi();
#endif