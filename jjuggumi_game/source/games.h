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
#define MUGUNWHA_MENT "무 궁 화 꽃 이 피 었 습 니 다"
#define NIGHTGAME_ALART1 "Player n obtained an item"
#define NIGHTGAME_ALART2 "Player n steals an item from Player n"

bool yh_killmode, get_item;
int fight;
int count;
int x, y;
int ingame_exchange_data;

int picked_jb, unpicked_jb;
int jb_pf[10]; // 제비 당첨 여부
int pl_cnt, r1; // 플레이어, 라운드 1
int jb_num;
int pl_now[10];
int jb_cnt, p_cnt;

/* 공통 영역 */
// ★ 사용자 움직임 정의
bool player_control(void);
// ★ NPC 움직임 정의
void move_random(int player, int dir);
// ★ back_buf[][]에 움직임 반영
void move_tail(int player, int nx, int ny);
// ★ 생존 플레이어 시각화
void player_visable(void);
// ★ 플레이어 스태미나 관리
void player_stamina(int p, int opt, int stamina_val);

/* "무궁화 꽃이 피었습니다" 영역 */
// ♨ "무궁화 꽃이 피었습니다" 메인
void mugunghwa(void);
// ♨ "무궁화 꽃이 피었습니다" 초기 설정
void mugunghwa_init(void);
// ♨ "무궁화 꽃이 피었습니다" NPC 움직임 정의
void npc_move_mugunghwa(void);
// ♨ "무궁화 꽃이 피었습니다" back_buf[][]에 움직임 반영
void move_tail_mugunghwa(int player, int nx, int ny);
// ♨ "무궁화 꽃이 피었습니다" 영희 행동 정의
void younghee(void);

/* "야간운동" 영역 */
// ★ "야간운동" 메인
void nightgame(void);
// ★ "야간운동" 초기 설정
void nightgame_init(void);
// ★ "야간운동" NPC 움직임 정의
void npc_move_nightgame(void);
// ★ "야간운동" 아이템 시각화
void nightgame_item_visable(void);

/* "줄다리기" 영역 */
// ♨ "줄다리기" 메인
void juldarigi(void);
// ♨ "줄다리기" 초기 설정
void juldarigi_init(void);
// ♨ "줄다리기" 게임 화면 - 내가 만든 것(보류) 
void map_init_juldarigi(int n_row, int n_col);

/* "제비뽑기" 영역 */
// ♨ "제비뽑기" 메인
void jebi(void);
// ♨ "제비뽑기" 초기 설정
void jebi_init(void);
//제비 섞기
void jebi_mix(int[]);
//제비 고르는 순서 정하기
void player_mix(int[]);
//제비 뽑기 조작
bool pick_jebi();
#endif