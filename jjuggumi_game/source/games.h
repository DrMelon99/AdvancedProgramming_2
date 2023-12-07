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
#define JULDARIGI_ALART1 "Player n fell into the hole"
#define JULDARIGI_ALART2 "LEFT Team lay down"
#define JULDARIGI_ALART3 "RIGHT Team lay down"

bool yh_killmode, get_item, break_cmd;
int fight, jebi_sel;
int game_cycle_count;
int x, y;
int jul_mid;
int ingame_exchange_data;

int juldarigi_team[2][5];
int jy[3]; // �� ��ǥ
double str_control; // ���Ӹ������� �ٴٸ��� �� ����
bool jul_lay_down[2]; // ���Ӹ������� �ٴٸ��� ���� ���� ���� [L:R]
double juldarigi_str[3]; // 0: ���� ��, 1: ���� ��, 2: ���� ��

int jebis[10][3];// 0: PASS / FAIL ����, 1: ���� ����, 2: �ش���ǥ


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
void can_move_mugunghwa(int player, int nx, int ny);

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
// �� "�ٴٸ���" ���Ӹ����� ��Ʈ��
void juldarigi_master_control(void);
// �� "�ٴٸ���" �� �̵�
void juldarigi_move(void);

/* "����̱�" ���� */
// �� "����̱�" ����
void jebi(void);
// �� "����̱�" �ʱ� ����
void jebi_init(void);
// �� "����̱�" ���� ����
void jebi_mix(void);
// �� "����̱�" ���� ����
bool jebi_select(void);


#endif