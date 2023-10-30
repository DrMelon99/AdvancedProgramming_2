#ifndef _GAMES_H_
#define _GAMES_H_

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

#define TIMER_MENT "�� �� ���ӽ���"

#define MUGUNWHA_MENT "�� �� ȭ �� �� �� �� �� �� ��"

void move_random(int player, int dir);
void move_tail(int player, int nx, int ny);

bool yh_killmode;

int count;


// [����ȭ ���� �Ǿ����ϴ�] �Լ�
void mugunghwa(void);

// [�߰��] �Լ�
void nightgame(void);

// [�ٴٸ���] �Լ�
void juldarigi(void); 

// [���� �̱�] �Լ�
void jebi(void); 


// [����ȭ ���� �Ǿ����ϴ�] �ʱ� ���� �Լ�
void mugunghwa_init(void);

// [�߰��] �ʱ� ���� �Լ�
void nightgame_init(void);

// [�ٴٸ���] �ʱ� ���� �Լ�
void juldarigi_init(void);

// [���� �̱�] �ʱ� ���� �Լ�
void jebi_init(void);

void younghee(void);

#endif