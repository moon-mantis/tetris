#include "tetris.h"
#include "display.h"
#include "error.h"
#include "utils.h"

#include <conio.h>
#include <time.h>
#include <assert.h>

bool game_loop(HANDLE screen_handle) {
	srand((unsigned)time(NULL));

	tetris_game_t game = {
		.board = { 0 },
		.current_shape = get_random_shape(),
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
	static const COORD OFFSET_LEFT = { .X = -1, .Y = 0};
	static const COORD OFFSET_RIGHT = { .X = 1, .Y = 0};
	static const COORD OFFSET_DOWN = { .X = 0, .Y = 1 };
	
	if (!_kbhit()) {
		return false;
	}

	switch (_getch()) {
	case QUIT_KEY:
		return true;
	case LEFT_KEY:
		try_moving_shape(game, OFFSET_LEFT);
		break;
	case RIGHT_KEY:
		try_moving_shape(game, OFFSET_RIGHT);
		break;
	case DOWN_KEY:
		try_moving_shape(game, OFFSET_DOWN);
		break;
	default:
		break;
	}

	return false;
}

bool try_moving_shape(tetris_game_t* game, COORD offset) {
	tetris_game_t new_game = *game;
	new_game.current_shape_position.X += offset.X;
	new_game.current_shape_position.Y += offset.Y;

	if (!is_shape_in_legal_position(new_game)) {
		return false;
	}

	game->current_shape_position = new_game.current_shape_position;
	return true;
}

bool is_shape_in_legal_position(tetris_game_t game) {
	tile_state_t current_shape_tile = 0;
	tile_state_t current_board_tile = 0;
	COORD current_board_tile_position = { 0 };
	for (size_t y = 0; y < game.current_shape.size; y++)
	{
		for (size_t x = 0; x < game.current_shape.size; x++)
		{
			current_shape_tile = game.current_shape.tiles[y * game.current_shape.size + x];
			if (current_shape_tile == EMPTY_TILE) {
				continue;
			}

			current_board_tile_position.X = game.current_shape_position.X + x;
			current_board_tile_position.Y = game.current_shape_position.Y + y;
			if (!is_in_bounds(current_board_tile_position)) {
				return false;
			}

			assert(current_board_tile_position.Y * BOARD_WIDTH + current_board_tile_position.X < BOARD_SIZE);
			current_board_tile = game.board[current_board_tile_position.Y * BOARD_WIDTH + current_board_tile_position.X];
			if (current_board_tile != EMPTY_TILE) {
				return false;
			}
		}
	}

	return true;
}
