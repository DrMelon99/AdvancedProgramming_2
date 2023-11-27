#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>

#include "jjuggumi.h"
#include "canvas.h"
#include "games.h"

#define PLAYER_MAX 10 // 최대 플레이어 수 10
#define ITEM_MAX 10

#define DIALOG_DURATION_SEC	4

bool player_statuspost[PLAYER_MAX];

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // 플레이어 수, 살아남은 플레이어 수, 이전 대조값
int n_item;
int game_round; // 현재 게임 라운드 수
int debug_i, debug_j, debug_k; // 디버깅 전용 변수

int tick[2];  // 시계

int pass_n_player;

typedef struct {
	int id;
	char name[100]; // 아이템 이름
	bool getable; // 아이템 소유 가능 여부
	int ix, iy; // 아이템 좌표 x,y
	int intel_buf, str_buf, stamina_buf; // 아이템의 지능, 힘, 스태미나 증가 능력치
} ITEM;

ITEM item[ITEM_MAX]; // ITEM 배열 인덱스의 최대치를 ITEM_MAX로 설정

typedef struct {
	int id; // 플레이어 번호
	int px, py; // 플레이어 좌표 x,y
	int period; // 플레이어 이동주기
	char name[100]; // 플레이어 이름
	int intel, str, stamina; // 플레이어 지능, 힘, 스태미나
	bool is_alive[2]; // 플레이어 생존 여부 0: 현재, 1: 이전 표시 대조 값
	bool hasitem, is_pass; // 아이템 소지여부, 게임통과 여부
	int interact_timestamp; // 상호작용 쿨타임
	ITEM item; // 플레이어가 가지고 있는 아이템 정보
} PLAYER;

PLAYER player[PLAYER_MAX]; // 플레이어 배열 인덱스의 최대치를 PLAYER_MAX로 설정

// main() 시작 시 쭈꾸미 게임 플레이어 수를 입력 받음
int jjuggumi_init(void);
// [쭈꾸미 게임 인트로] 함수
void intro(void);
// [쭈꾸미 게임 엔딩] 함수
void ending(void);
// [간단한 예시 샘플] 함수
void sample(void);

#endif
