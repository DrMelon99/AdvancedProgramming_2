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

#define DIALOG_DURATION_SEC		4

bool player_status[PLAYER_MAX];  // 기본값 true, 탈락하면 false
bool player_statuspost[PLAYER_MAX];

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

int player_outlist[PLAYER_MAX];
int n_player, n_alive, n_alivepost; // 플레이어 수, 살아남은 플레이어 수, 이전 대조값
int tick;  // 시계
int pass_n_player;


int jjuggumi_init(void); // main() 시작 시 쭈꾸미 게임 플레이어 수를 입력 받음



// ===== 기타 목록 =====
void intro(void); // [쭈꾸미 게임 인트로] 함수
void ending(void);// [쭈꾸미 게임 엔딩] 함수
void sample(void); // [간단한 예시 샘플] 함수

void move_random(int player, int dir);
void move_tail(int player, int nx, int ny);

#endif
