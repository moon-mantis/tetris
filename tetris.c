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

	UINT64 current_time = 0;
	UINT64 delta_time = 0;
	
	current_time = get_absolute_time_in_ms();

	while (true) {
		delta_time = get_absolute_time_in_ms() - current_time;
		current_time += delta_time;

		if (handle_delta_time(&game, delta_time)) {
			_cprintf("You lost :(\n\n");
			break;
		}

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
	case LEFT_KEY:
		try_moving_shape(game, OFFSET_LEFT);
		break;
	case RIGHT_KEY:
		try_moving_shape(game, OFFSET_RIGHT);
		break;
	case DOWN_KEY:
		if (try_moving_shape(game, OFFSET_DOWN)) {
			game->time_since_last_drop = 0;
		}
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

	if (!is_current_shape_in_legal_position(new_game)) {
		return false;
	}

	game->current_shape_position = new_game.current_shape_position;
	return true;
}

bool is_current_shape_in_legal_position(tetris_game_t game) {
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

bool handle_delta_time(tetris_game_t* game, UINT64 delta_time) {
	game->time_since_last_drop += delta_time;

	bool shape_should_drop = game->time_since_last_drop >= AUTOMATIC_DROP_TIME;
	if (!shape_should_drop) {
		return false;
	}

	bool move_worked = try_moving_shape(game, OFFSET_DOWN);
	if (move_worked) {
		game->time_since_last_drop -= AUTOMATIC_DROP_TIME;
		return false;
	}

	place_piece(game);
	game->current_shape = get_random_shape();
	game->current_shape_position = SHAPE_STARTING_POSITION;

	return !is_current_shape_in_legal_position(*game);
}

void place_piece(tetris_game_t* game) {
	tile_state_t current_shape_tile = 0;
	tile_state_t current_board_tile = 0;
	COORD current_board_tile_position = { 0 };
	size_t current_board_tile_index = 0;
	for (size_t y = 0; y < game->current_shape.size; y++)
	{
		for (size_t x = 0; x < game->current_shape.size; x++)
		{
			current_shape_tile = game->current_shape.tiles[y * game->current_shape.size + x];
			if (current_shape_tile == EMPTY_TILE) {
				continue;
			}

			current_board_tile_position.X = game->current_shape_position.X + x;
			current_board_tile_position.Y = game->current_shape_position.Y + y;
			assert(is_in_bounds(current_board_tile_position));

			current_board_tile_index = current_board_tile_position.Y * BOARD_WIDTH + current_board_tile_position.X;
			assert(current_board_tile_index < BOARD_SIZE);
			assert(game->board[current_board_tile_index] == EMPTY_TILE);

			game->board[current_board_tile_index] = current_shape_tile;
		}
	}
}