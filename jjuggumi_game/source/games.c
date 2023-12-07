#include "keyin.h"
#include "games.h"

bool player_control(void)
{
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir = 0;  // 움직일 방향(0~3)

	key_t key = get_key();
	if (key == K_QUIT)
	{
		return true;
	}
	else if (key == K_SPACE)
	{
		return false;
	}
	else if ((key == K_UP) || (key == K_DOWN) || (key == K_LEFT) || (key == K_RIGHT))
	{
		switch (key)
		{
		case K_UP: dir = DIR_UP; break;
		case K_DOWN: dir = DIR_DOWN; break;
		case K_LEFT: dir = DIR_LEFT; break;
		case K_RIGHT: dir = DIR_RIGHT; break;
		}

		int nx = player[0].px + dx[dir];
		int ny = player[0].py + dy[dir];

		if (!placable(nx, ny))
			return false;

		if (game_round == 1)
		{
			if(player[0].is_alive[0] == true)
				can_move_mugunghwa(0, nx, ny);
		}
		else
		{
			move_tail(0, nx, ny);
		}
		return false;
	}
	else if (key == K_DEBUG)
	{
		debug_toggle = !debug_toggle;
		return false;
	}
	else
	{
		return false;
	}
}

void move_random(int p, int dir)
{
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do
	{
		nx = player[p].px + randint(-1, 1);
		ny = player[p].py + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void move_tail(int p, int nx, int ny)
{
	back_buf[nx][ny] = back_buf[player[p].px][player[p].py];
	back_buf[player[p].px][player[p].py] = ' ';
	player[p].px = nx;
	player[p].py = ny;
}

void player_visable(void)
{
	for (int i = 0; i < n_player; i++)
	{
		if ((player[i].is_alive[0] == true) && (player[i].is_pass == false))
		{
			back_buf[player[i].px][player[i].py] = '0' + i;
		}
		else
		{
			back_buf[player[i].px][player[i].py] = ' ';
		}
	}
}

void player_stamina(int p, int opt, int stamina_val)
{
	if (opt == 0) // 라운드 종료
	{
		for (int i = 0; i < n_player; i++)
		{
			player[i].stamina += randint(40, 50);

			if (player[i].stamina > 100)
			{
				player[i].stamina = 100;
			}
			else if (player[i].stamina < 0)
			{
				player[i].stamina = 0;
			}
		}
	}
	else if (opt == 1) // 특정 플레리어 스태미나 조정
	{
		player[p].stamina += stamina_val;

		if (player[p].stamina > 100)
		{
			player[p].stamina = 100;
		}
		else if (player[p].stamina < 0)
		{
			player[p].stamina = 0;
		}
	}
}

void npc_move_mugunghwa(void)
{
	int nx, ny, move_rand;  // 다음에 놓일 자리

	for (int p = 1; p < n_player; p++)
	{
		if ((tick[0] % player[p].period == 0) && (player[p].is_pass == false) && (player[p].is_alive[0] == true))
		{
			do
			{
				move_rand = randint(0, 1000);

				if (move_rand < 900) // NPC 앞으로 -> 90% / 영희의 킬모드가 켜질 경우 NPC 제자리 -> 90%
				{
					nx = player[p].px;
					if (yh_killmode == true)
						ny = player[p].py;
					else
						ny = player[p].py - 1;
				}
				else if ((move_rand >= 900) && (move_rand < 930)) // NPC 위로 -> 3%
				{
					nx = player[p].px - 1;
					ny = player[p].py;
				}
				else if ((move_rand >= 930) && (move_rand < 960)) // NPC 아래로 -> 3%
				{
					nx = player[p].px + 1;
					ny = player[p].py;
				}
				else // NPC 제자리 -> 4% / 영희의 킬모드가 켜질 경우 NPC 앞으로 4%
				{
					nx = player[p].px;
					if (yh_killmode == true)
						ny = player[p].py - 1;
					else
						ny = player[p].py;
				}
			} while (!placable(nx, ny));

			can_move_mugunghwa(p, nx, ny);
		}
	}
}

void can_move_mugunghwa(int p, int nx, int ny)
{
	for (int i = 0; i < n_player; i++) // 가려져 있으면 지나감
	{
		if ((player[i].is_pass == false) && (player[i].px == nx) && (player[i].py < ny))
		{
			move_tail(p, nx, ny);
			return 0;
		}
	}

	if ((ny == 1) || ((ny == 2) && ((nx > 5) && (nx < 9)))) // 도착 조건
	{
		player[p].is_pass = true;
		move_tail(p, nx, ny);
		return 0;
	}

	if (((player[p].px != nx) || (player[p].py != ny)) && (player[p].is_pass == false) && (yh_killmode == true))
	{
		player[p].is_alive[0] = false;
		n_alive--;
		ingame_exchange_data++;
	}
	else
	{
		move_tail(p, nx, ny);
	}
	return 0;
}

void npc_move_nightgame(void)
{
	int nx, ny;  // 다음에 놓일 자리
	bool found;

	for (int p = 1; p < n_player; p++)
	{
		if ((tick[0] % player[p].period == 0) && (player[p].is_alive[0] == true))
		{
			found = false;

			for (int i = -5; i < 6 && !found; i++)
			{
				for (int j = -5; j < 6 && !found; j++)
				{
					if ((i == 0) && (j == 0))
						continue;

					// 아이템 쪽으로 이동
					for (int k = 0; k < n_item && !found; k++)
					{
						if ((player[p].px + i == item[k].ix) && (player[p].py + j == item[k].iy) &&
							((player[p].hasitem == false) || (player[p].stamina == 0)) && (item[k].getable == true))
						{
							if (i < 0)
								nx = player[p].px - 1;
							else if (i > 0)
								nx = player[p].px + 1;
							else
								nx = player[p].px;

							if (j < 0)
								ny = player[p].py - 1;
							else if (j > 0)
								ny = player[p].py + 1;
							else
								ny = player[p].py;

							if (!placable(nx, ny))
								continue;

							found = true;
						}
					}

					// 플레이어 쪽으로 이동
					for (int k = 0; k < n_player && !found; k++)
					{
						if ((player[p].px + i == player[k].px) && (player[p].py + j == player[k].py) &&
							(player[k].hasitem == true) && (player[k].is_alive[0] == true) && (player[k].stamina > 0))
						{
							if (i < 0)
								nx = player[p].px - 1;
							else if (i > 0)
								nx = player[p].px + 1;
							else
								nx = player[p].px;

							if (j < 0)
								ny = player[p].py - 1;
							else if (j > 0)
								ny = player[p].py + 1;
							else
								ny = player[p].py;

							if (!placable(nx, ny))
								continue;

							found = true;
						}
					}
				}
			}

			// 아이템 및 플레이어를 찾지 못하거나 해당 두개와 상호작용한지 3초가 지나지 않았다면
			// 랜덤으로 움직이기
			if (found == false || (tick[0] - player[p].interact_timestamp < 3000))
			{
				do
				{
					nx = player[p].px + randint(-1, 1);
					ny = player[p].py + randint(-1, 1);
				} while (!placable(nx, ny));
			}

			move_tail(p, nx, ny);
		}
	}
}

void nightgame_item_visable(void)
{
	for (int i = 0; i < n_item; i++)
	{
		// getable 여부에 따른 아이템 시각화
		if (item[i].getable == true)
		{
			back_buf[item[i].ix][item[i].iy] = '$';
		}
		else if (back_buf[item[i].ix][item[i].iy] == '$')
		{
			back_buf[item[i].ix][item[i].iy] = ' ';
		}
	}
}

void juldarigi_master_control(void)
{
	key_t key = get_key();

	if (key == K_PULL_LEFT)
	{
		str_control -= 1.0;
		Beep(SOUND_D, 5);
	}
	else if (key == K_PULL_RIGHT)
	{
		str_control += 1.0;
		Beep(SOUND_D, 5);
	}
	else if ((key == K_LAYDOWN_LEFT) && (jul_lay_down[0] == false))
	{
		jul_lay_down[0] = true; // 눕기 활성화
		print_addi_status(0, -1, -1);
		print_addi_status(6, 1, -1);
		tick[1] = tick[0];
		Beep(SOUND_D, 5);
	}
	else if ((key == K_LAYDOWN_RIGHT) && (jul_lay_down[1] == false))
	{
		jul_lay_down[1] = true; // 눕기 활성화
		print_addi_status(0, -1, -1);
		print_addi_status(6, 2, -1);
		tick[1] = tick[0];
		Beep(SOUND_D, 5);
	}
	else if (key == K_DEBUG)
	{
		debug_toggle = !debug_toggle;
	}
	else if (key == K_QUIT)
	{
		break_cmd = true;
	}
}

void juldarigi_move(void)
{
	// 오른쪽으로 줄 당김
	if (juldarigi_str[0] > 0.0)
	{
		if (jy[0] != jul_mid)
		{
			for (int i = 0; i < n_player; i++)
			{
				move_tail(i, player[i].px, player[i].py + 1);
			}
			for (int i = 0; i < 3; i++)
			{
				jy[i]++;
				back_buf[4][jy[i]] = '-';
			}
		}
		else
		{
			for (int i = 0; i < n_player; i++)
			{
				if ((player[i].py == (jy[0] - 1)) && (player[i].is_alive[0] == true))
				{
					player[i].is_alive[0] = false;
					player[i].stamina = 0;
					n_alive--;
					print_addi_status(0, -1, -1);
					print_addi_status(5, player[i].id, -1);

					for (int j = player[i].id + 2; j < n_player; j += 2)
					{
						move_tail(j, player[j].px, player[j].py + 1);
					}
					break;
				}
			}
		}
	}
	// 왼쪽으로 줄 당김
	else if (juldarigi_str[0] < 0.0)
	{
		if (jy[2] != jul_mid)
		{
			for (int i = 0; i < n_player; i++)
			{
				move_tail(i, player[i].px, player[i].py - 1);
			}
			for (int i = 0; i < 3; i++)
			{
				jy[i]--;
				back_buf[4][jy[i]] = '-';
			}
		}
		else
		{
			for (int i = 0; i < n_player; i++)
			{
				if ((player[i].py == (jy[2] + 1)) && (player[i].is_alive[0] == true))
				{
					player[i].is_alive[0] = false;
					player[i].stamina = 0;
					n_alive--;
					print_addi_status(0, -1, -1);
					print_addi_status(5, player[i].id, -1);

					for (int j = player[i].id + 2; j < n_player; j += 2)
					{
						move_tail(j, player[j].px, player[j].py - 1);
					}
					break;
				}
			}
		}
	}
}

void jebi_mix(void)
{
	int fail_jebi = randint(0, n_alive-1);
	int print_count = 0;
	int middle_ROW = N_ROW / 2; // 제비 좌표 높이 결정
	int start_COL = (N_COL / 2) - ((n_alive - 1) * 2); // 제비 좌표 가로 시작 위치 결정 (가운데 유지하기 위함)

	for (int i = 0; i < n_alive; i++)
	{
		jebis[i][1] = 0; // 모두 미개봉 설정

		if (i == fail_jebi)
			jebis[i][0] = 0;
		else
			jebis[i][0] = 1;
	}

	for (int i = n_alive; i < 10; i++)
	{
		jebis[i][1] = 2; // 제 3의 상태 Unable
	}

	for (int i = 0; i < n_alive; i++)
	{
		jebis[i][2] = start_COL + print_count;
		back_buf[3][start_COL + print_count++] = '?';

		for (int j = 0; j < 3; j++)
			back_buf[3][j + print_count++] = ' ';
	}
}

bool jebi_select(void)
{
	jebi_sel = 0;

	while (1)
	{
		for (int i = 0; i < n_alive; i++)
		{
			back_buf[4][jebis[i][2]] = ' ';

			if(jebis[i][1] == 0)
				back_buf[3][jebis[i][2]] = '?';
			else
				back_buf[3][jebis[i][2]] = '@';
		}

		while (jebis[jebi_sel][1] == 1)
		{
			jebi_sel++;
		}

		back_buf[4][jebis[jebi_sel][2]] = '^';

		key_t key = get_key();

		if (key == K_LEFT)
		{
			Beep(SOUND_D, 5);

			do
			{
				if (jebi_sel == 0)
					jebi_sel = n_alive - 1;
				else
					jebi_sel--;
			} while (jebis[jebi_sel][1] == 1);
		}
		else if (key == K_RIGHT)
		{
			Beep(SOUND_D, 5);

			do
			{
				if (jebi_sel == n_alive - 1)
					jebi_sel = 0;
				else
					jebi_sel++;
			} while (jebis[jebi_sel][1] == 1);
		}
		else if (key == K_SPACE)
		{
			Beep(SOUND_D * 2, 5);
			return false;
		}
		else if (key == K_DEBUG)
		{
			debug_toggle = !debug_toggle;
		}
		else if (key == K_QUIT)
		{
			return true;
		}

		display();
		Sleep(10);
		tick[0] += 10;
	}
}

