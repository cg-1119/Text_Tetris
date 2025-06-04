#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "include/common.h"
#include "include/logic.h"

int main(void)
{
	/*
		About XTerm Control Sequences:
        https://invisible-island.net/xterm/ctlseqs/ctlseqs.html

		Enable alternate screen buffer(1049h), Disable auto-wrap mode(7l)
	*/
	printf("\x1b[?1049h\x1b[?7l");
	srand((unsigned)time(NULL));

	int menu = 1;

	while (menu)
	{
		menu = display_menu();

		if (menu == 1)
		{
			game = GAME_START;
			menu = game_start();
		}
		else if (menu == 2)
			search_result();

		else if (menu == 3)
			print_result();

		else if (menu == 4)
			break;
	}

	//Restore screen buffer(1049l), Enable auto-wrap mode(7h)
	printf("\x1b[?1049l\x1b[?7h");
	return 0;
}