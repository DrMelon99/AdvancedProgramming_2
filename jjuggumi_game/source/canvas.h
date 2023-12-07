#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// 화면 크기(맵 크기x. 맵 + 상태창)
#define ROW_MAX		40
#define COL_MAX		80

// 더블 버퍼링
// back_buf[][]가 맵이고,
// front_buf[][]는 화면에 출력하기 위한 정보
// 참고: https://codevang.tistory.com/39
// 윈도우API로도 가능: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];
char temp_buf[ROW_MAX][COL_MAX];

// 맵 크기(위의 buf는 텍스트까지 포함한 캔버스 크기)
int N_ROW, N_COL;

bool debug_toggle;

// ★ 상단에 맵을, 하단에는 현재 상태를 출력
void display(void);
// ★ 변경점이 있는 맵 좌표에 출력
void draw(void);
// ★ (zero-base) row행, col열로 커서 이동
void gotoxy(int x, int y);
// ★ row행, col열에 ch 출력
void printxy(char ch, int row, int col);
// ★ 상태 출력
void print_status(void);
// ★ 두 버퍼를를 완전히 비우고 맵의 외곽을 '*'로 구성 (게임 초기 설정 시 실행)
void map_init(int n_row, int n_col);
// ★ back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col);

// ★ 현재 back_buf를 temp_buf에 저장
void memory_front_buf(void);
// ★ 마지막에 저장했던 temp_buf를 back_buf에 복원
void restore_front_buf(void);
// 추가 정보 출력
void print_addi_status(int opt, int p, int data);
// ★ 입력된 opt에 따른 다이얼로그 출력
void dialog(int opt, int data);

// ★ 두 버퍼를를 완전히 비우고 맵의 외곽을 '*'로 구성 (게임 초기 설정 시 실행) (줄다리기 전용)
void map_init_juldarigi(int n_row, int n_col);

#endif