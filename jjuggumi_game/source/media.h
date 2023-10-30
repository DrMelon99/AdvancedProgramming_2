#ifndef _MEDIA_H_
#define _MEDIA_H_

// ===== ���� ��� =====
#define SOUND_C 1046.502 // ��
#define SOUND_Csharp 1108.731 // ��#
#define SOUND_D 1108.731 // ��
#define SOUND_Dsharp 1244.508 // ��#
#define SOUND_E 1318.510 // ��
#define SOUND_F 1396.913 // ��
#define SOUND_Fsharp 1479.978 // ��#
#define SOUND_G 1567.982 // ��
#define SOUND_Gsharp 1661.219 // ��#
#define SOUND_A 1760.000 // ��
#define SOUND_Asharp 1864.655 // ��#
#define SOUND_B 1975.533

// �ٹٲ� ���
void enline(int n, int m);

// ��Ʈ�� Ÿ��Ʋ �ƽ�Ű ��Ʈ
void introtitle(int n);

// ���� ��� �Լ�
void titlesong(void);

// ����ȭ ���� �Ǿ����ϴ� �뷡 ��� �Լ�
void mugunghwasong(int sound);

// �ܼ� â�� ��Ʈ ũ�� ����
void SetConsoleFontSize(int size);

#endif