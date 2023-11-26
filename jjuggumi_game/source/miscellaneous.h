#ifndef _MISC_H_
#define _MISC_H_

// ===== 음계 목록 =====
#define SOUND_C 1046.502 // 도
#define SOUND_Csharp 1108.731 // 도#
#define SOUND_D 1108.731 // 레
#define SOUND_Dsharp 1244.508 // 레#
#define SOUND_E 1318.510 // 미
#define SOUND_F 1396.913 // 파
#define SOUND_Fsharp 1479.978 // 파#
#define SOUND_G 1567.982 // 솔
#define SOUND_Gsharp 1661.219 // 솔#
#define SOUND_A 1760.000 // 라
#define SOUND_Asharp 1864.655 // 라#
#define SOUND_B 1975.533 // 시

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high);

// 줄바꿈 기능
void enline(int n, int m);

// 인트로 타이틀 아스키 아트
void introtitle(int n);

// 음악 재생 함수
void titlesong(void);

// 무궁화 꽃이 피었습니다 노래 재생 함수
void mugunghwasong(int sound);

// 콘솔 창의 폰트 크기 조정
void SetConsoleFontSize(int size);

// 콘솔 커서 숨김
void system_cursor(void);

#endif