#include "games.h"

void jebi(void)
{
	jebi_init();

	dialog(0, -1);
	count = 1;
	picked_jb = 3;
	pl_cnt = 0, p_cnt = 0, r1 = 0;
	jb_num = 0;
	jb_cnt = n_alive;
	while (1) // ���� ���� ����
	{
		if (pick_jebi() == true || n_alive == 1) 
			break;  //���� �ȳ���

		if (r1 == 0) {
			player_mix(pl_now);
			ingame_exchange_data = player[pl_now[0]].id;
			jebi_mix(jb_pf);
			r1++;
		}

		unpicked_jb = 0; // �÷��̾� ���� ���� ���� ��ġ�ϱ�
		for (int i = 0; i < jb_cnt; i++) {
			unpicked_jb += 3;
			back_buf[3][unpicked_jb] = '?';
		}
		back_buf[3][picked_jb] = '@';


		/*
		for (int i = 0; i < n_alive; i++) {
			back_buf[2][(i + 1) * 3] = jb_pf[i];		//�׽�Ʈ��
		}
		for (int i = 0; i < 10; i++) {
			printf("%d ", player[pl_now[i]].id);
		}
		printf("%d", n_player);
		*/
		
		display();
		Sleep(10);
		tick[0] += 10;
	}
}

void jebi_init(void)
{
	game_round = 4;

	system("cls");

	map_init(7, 34);

	SetConsoleFontSize(20);
	system("mode con: cols=34 lines=15");
}