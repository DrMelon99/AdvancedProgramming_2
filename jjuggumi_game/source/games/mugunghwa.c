void mugunghwa(void)
{
	mugunghwa_init();

	display();

	//for (int i = DIALOG_DURATION_SEC; i > 0; i--)
	//{
	//	strcat(send_message, (char)i);
	//	strcat(send_message, TIMER_MENT);

	//	printf("%s\n", send_message);

	//	// dialog(strcat((char)i, "초 후 게임시작"));
	//}

	while (1)
	{
		// 여기에 영희가 "무궁화 꽃이 피었습니다" 말하기 배치

		// 여기에 사용자 움직임 배치
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// 여기에 다른 NPC 랜덤 움직임 배치
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}

void mugunghwa_init(void)
{
	system("cls");

	SetConsoleFontSize(20);
	system("mode con: cols=40 lines=30");

	map_init(12, 40);

	// 해당 영역은 플레이어 우측 시작 지점 랜덤 배치
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = (N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}



	//여기에 영희 배치


	tick = 0;
}