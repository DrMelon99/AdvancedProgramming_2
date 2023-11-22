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

#define TIMER_MENT "초 후 게임시작"
#define MUGUNWHA_MENT "무 궁 화 꽃 이 피 었 습 니 다"

bool yh_killmode, get_item;
int count;
int x, y;

void move_random(int player, int dir);
void move_manual(key_t key);
void move_tail(int player, int nx, int ny);

void move_random_mugunghwa(int player, int dir);
void move_tail_mugunghwa(int player, int nx, int ny);

void move_random_nightgame(int p, int dir);
void move_tail_nightgame(int p, int nx, int ny);

void mugunghwa(void);
void nightgame(void);
void juldarigi(void);
void jebi(void);

void mugunghwa_init(void);
void nightgame_init(void);
void juldarigi_init(void);
void jebi_init(void);


void younghee(void);

void player_stamina(int p, int opt);

#endif