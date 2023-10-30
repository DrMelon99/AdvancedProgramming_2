#ifndef _GAMES_H_
#define _GAMES_H_

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

#define TIMER_MENT "초 후 게임시작"

#define MUGUNWHA_MENT "무 궁 화 꽃 이 피 었 습 니 다"

void move_random(int player, int dir);
void move_tail(int player, int nx, int ny);

bool yh_killmode;

int count;


// [무궁화 꽃이 피었습니다] 함수
void mugunghwa(void);

// [야간운동] 함수
void nightgame(void);

// [줄다리기] 함수
void juldarigi(void); 

// [제비 뽑기] 함수
void jebi(void); 


// [무궁화 꽃이 피었습니다] 초기 진입 함수
void mugunghwa_init(void);

// [야간운동] 초기 진입 함수
void nightgame_init(void);

// [줄다리기] 초기 진입 함수
void juldarigi_init(void);

// [제비 뽑기] 초기 진입 함수
void jebi_init(void);

void younghee(void);

#endif