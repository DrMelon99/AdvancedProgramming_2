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

#define MUGUNWHA_MENT "�� �� ȭ �� �� �� �� �� �� ��"

bool yh_killmode, get_item;
int fight;
int count;
int x, y;

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
// �� "�߰��" back_buf[][]�� ������ �ݿ�
void move_tail_nightgame(int p, int nx, int ny);
// �� "�߰��" ������ �ð�ȭ
void nightgame_item_visable(void);

/* "�ٴٸ���" ���� */
// �� "�ٴٸ���" ����
void juldarigi(void);
// �� "�ٴٸ���" �ʱ� ����
void juldarigi_init(void);

/* "����̱�" ���� */
// �� "����̱�" ����
void jebi(void);
// �� "����̱�" �ʱ� ����
void jebi_init(void);

#endif