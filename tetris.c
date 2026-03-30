#include "tetris.h"
#include "display.h"
#include "error.h"

#include <conio.h>

bool game_loop(HANDLE screen_handle) {
	tetris_game_t game = {
		.board = { 0 },
		.current_shape = Z_SHAPE,
		.current_shape_position = SHAPE_STARTING_POSITION
	};

	while (true) {
		if (handle_input(&game)) {
			break;
		}

		if (!render_and_display_game(screen_handle, game)) {
			print_last_error("printing game");
			return false;
		}
	}

	return true;
}

bool handle_input(tetris_game_t* game) {
	if (!_kbhit()) {
		return false;
	}

	switch (_getch()) {
	case QUIT_KEY:
		return true;
	default:
		break;
	}

	return false;
}
