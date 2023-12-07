#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// ȭ�� ũ��(�� ũ��x. �� + ����â)
#define ROW_MAX		40
#define COL_MAX		80

// ���� ���۸�
// back_buf[][]�� ���̰�,
// front_buf[][]�� ȭ�鿡 ����ϱ� ���� ����
// ����: https://codevang.tistory.com/39
// ������API�ε� ����: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];
char temp_buf[ROW_MAX][COL_MAX];

// �� ũ��(���� buf�� �ؽ�Ʈ���� ������ ĵ���� ũ��)
int N_ROW, N_COL;

bool debug_toggle;

// �� ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void);
// �� �������� �ִ� �� ��ǥ�� ���
void draw(void);
// �� (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int x, int y);
// �� row��, col���� ch ���
void printxy(char ch, int row, int col);
// �� ���� ���
void print_status(void);
// �� �� ���۸��� ������ ���� ���� �ܰ��� '*'�� ���� (���� �ʱ� ���� �� ����)
void map_init(int n_row, int n_col);
// �� back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col);

// �� ���� back_buf�� temp_buf�� ����
void memory_front_buf(void);
// �� �������� �����ߴ� temp_buf�� back_buf�� ����
void restore_front_buf(void);
// �߰� ���� ���
void print_addi_status(int opt, int p, int data);
// �� �Էµ� opt�� ���� ���̾�α� ���
void dialog(int opt, int data);

// �� �� ���۸��� ������ ���� ���� �ܰ��� '*'�� ���� (���� �ʱ� ���� �� ����) (�ٴٸ��� ����)
void map_init_juldarigi(int n_row, int n_col);

#endif