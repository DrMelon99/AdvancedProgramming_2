#include "games.h"

void juldarigi(void)
{
	juldarigi_init();

	dialog(0, -1);

	while (1) // ���� ���� ����
	{
		if (break_cmd == true)
			break;

		int dead[2] = { 0, };
		for (int i = 0; i < n_player / 2; i++) // ���� �� �� ���̶� ���� ���� 0�̸� ���� ����
		{
			if (player[juldarigi_team[0][i]].is_alive[0] == false)
				dead[0]++;
			if (player[juldarigi_team[1][i]].is_alive[0] == false)
				dead[1]++;
			if ((dead[0] == n_player / 2) || (dead[1] == n_player / 2))
				break_cmd = true;
		}
			
		player_visable();

		// ���ۿ� ���� �÷��̾�, ���� ��� 1�� ���� ��� �� ����
		if (tick[0] - tick[1] > 1000)
			print_addi_status(0, -1, -1);

		// ���� �⺻ �� �ջ�
		juldarigi_str[1] = juldarigi_str[2] = 0; // ���� �� �ջ� �ʱ�ȭ

		for (int i = 0; i < n_player / 2; i++) // ���� �ٴٸ��� ������ str�� ����
		{
			if (player[juldarigi_team[0][i]].is_alive[0] == true)
			{
				juldarigi_str[1] += (player[juldarigi_team[0][i]].str + player[juldarigi_team[0][i]].item.str_buf) * (player[juldarigi_team[0][i]].stamina / 100.0);
			}
			if (player[juldarigi_team[1][i]].is_alive[0] == true)
			{
				juldarigi_str[2] += (player[juldarigi_team[1][i]].str + player[juldarigi_team[1][i]].item.str_buf) * (player[juldarigi_team[1][i]].stamina / 100.0);
			}
		}

		// ���Ӹ������� ���� ����
		juldarigi_master_control();

		if (jul_lay_down[0])
			juldarigi_str[1] *= 2;
		if (jul_lay_down[1])
			juldarigi_str[2] *= 2;

		// ���� ��� �� �ջ�
		juldarigi_str[0] = juldarigi_str[2] - juldarigi_str[1] + str_control;

		//  ���� �� �� �� �� ��� (3�� ����)
		if (tick[0] - tick[2] > 3000)
		{
			if (jul_lay_down[0] != jul_lay_down[1]) // �� �� �����̶� ������ ��� ���� �� ������ ��ĭ ���
				juldarigi_move();
			juldarigi_move();
			
			Beep(SOUND_D * 2, 5);

			tick[1] = tick[0];

			str_control = 0.0;

			for (int i = 0; i < n_player / 2; i++) // ������ �������� ���¹̳� 30% ����
			{
				if ((jul_lay_down[0] == true) && (player[juldarigi_team[0][i]].is_alive[0] == true))
					player_stamina(juldarigi_team[0][i], 1, -30);
				if ((jul_lay_down[1] == true) && player[juldarigi_team[1][i]].is_alive[0] == true)
					player_stamina(juldarigi_team[1][i], 1, -30);
			}

			for (int i = 0; i < 2; i++) // ���� �� �ʱ�ȭ
				jul_lay_down[i] = false;

			tick[2] = tick[0];
		}

		display();
		Sleep(10);
		tick[0] += 10;
	}

	n_alive = 0;

	for (int i = 0; i < n_player; i++)
	{
		if (player[i].is_alive[1] == true)
		{
			if (player[i].is_alive[0] == false)
			{
				player[i].intel /= 2;
				player[i].str /= 2;
				player[i].hasitem = false;
				player[i].item.getable = true;;
				player[i].item.intel_buf = 0;
				player[i].item.str_buf = 0;
			}
			player[i].is_alive[0] = true;
			n_alive++;
		}
		else
		{
			if (player[i].is_alive[0] == true)
			{
				player[i].is_alive[0] = true;
				n_alive++;

			}
			else
			{
				player[i].is_alive[0] = false;
			}
		}
	}

	player_stamina(-1, 0, -1);
}

void juldarigi_init(void)
{
	game_round = 3;

	system("cls");

	map_init_juldarigi(9, 32);

	SetConsoleFontSize(20);
	system("mode con: cols=32 lines=30");

	n_alive = n_player;

	break_cmd = false;

	for (int i = 0; i < 3; i++)
		juldarigi_str[i] = 0;

	// ���� Ż�����θ� is_alive[1]�� ���
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_alive[1] = player[i].is_alive[0];

		player[i].is_alive[0] = true;
	}

	// ���� �߾��� �߽����� 3�� ������ �� ����
	for (int i = 0; i < 3; i++)
	{
		jy[i] = (jul_mid - 1) + i;
		back_buf[4][(jul_mid - 1) + i] = '-';
	}

	for (int i = 0; i < n_player; i++) // �÷��̾� ��ġ
	{
		player[i].px = 4;

		if (i % 2 == 0)
		{
			player[i].py = (jul_mid - 2) - (i / 2);
			juldarigi_team[0][i / 2] = player[i].id;
		}
		else
		{
			player[i].py = (jul_mid + 2) + (i / 2);
			juldarigi_team[1][i / 2] = player[i].id;
		}
			
	}

	str_control = 0.0;

	for(int i = 0; i < 2;i++)
		jul_lay_down[i] = false;
	
	debug_toggle = false;

	for (int i = 0; i < 3; i++)
		tick[i] = 0;
}