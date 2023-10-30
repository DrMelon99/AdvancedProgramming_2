void mugunghwa(void)
{
	mugunghwa_init();

	display();

	//for (int i = DIALOG_DURATION_SEC; i > 0; i--)
	//{
	//	strcat(send_message, (char)i);
	//	strcat(send_message, TIMER_MENT);

	//	printf("%s\n", send_message);

	//	// dialog(strcat((char)i, "�� �� ���ӽ���"));
	//}

	while (1)
	{
		// ���⿡ ���� "����ȭ ���� �Ǿ����ϴ�" ���ϱ� ��ġ

		// ���⿡ ����� ������ ��ġ
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// ���⿡ �ٸ� NPC ���� ������ ��ġ
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

	// �ش� ������ �÷��̾� ���� ���� ���� ���� ��ġ
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);
			y = (N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}



	//���⿡ ���� ��ġ


	tick = 0;
}