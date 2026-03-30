#include "tetris.h"
#include "display.h"
#include "error.h"

#include <conio.h>

bool game_loop(HANDLE screen_handle) {
	tetris_game_t game = {
		.board = { 0 }
	};

	while (true) {
		if (!render_and_print_game(screen_handle, game)) {
			print_last_error("printing game");
			return false;
		}
	}

	return true;
}
