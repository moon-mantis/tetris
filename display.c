#include "display.h"
#include "tetris.h"
#include "shape.h"

#include <assert.h>

BOOL render_and_display_game(HANDLE screen_handle, tetris_game_t game) {
	CHAR_INFO character_board[BOARD_SIZE] = { 0 };
	static const COORD BOARD_DIMENSIONS = { .X = BOARD_WIDTH, .Y = BOARD_HEIGHT };
	SMALL_RECT write_region = BOARD_WRITE_REGION;

	render_board(character_board, game.board);
	render_shape(character_board, game.current_shape, game.current_shape_position);

	return WriteConsoleOutput(
		screen_handle,
		character_board,
		BOARD_DIMENSIONS,
		ORIGIN,
		&write_region
	);
}

void render_board(CHAR_INFO character_board[BOARD_SIZE], const tile_state_t board[BOARD_SIZE]) {
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		switch (board[i]) {
		case EMPTY_TILE:
			character_board[i] = EMPTY_TILE_CHAR_INFO;
			break;
		case FULL_TILE:
			character_board[i] = FULL_TILE_CHAR_INFO;
			break;
		}
	}
}

void render_shape(CHAR_INFO display_board[BOARD_SIZE], shape_t shape, COORD position)
{
	COORD current_board_position = { 0 };
	tile_state_t current_shape_tile = 0;

	for (size_t current_shape_position_y = 0; current_shape_position_y < shape.size; current_shape_position_y++)
	{
		for (size_t current_shape_position_x = 0; current_shape_position_x < shape.size; current_shape_position_x++)
		{
			current_shape_tile = shape.tiles[current_shape_position_y * shape.size + current_shape_position_x];
			if (current_shape_tile == EMPTY_TILE) {
				continue;
			}

			current_board_position.X = position.X + current_shape_position_x;
			current_board_position.Y = position.Y + current_shape_position_y;
			if (!is_in_bounds(current_board_position)) {
				continue;
			}

			assert(current_shape_tile == FULL_TILE);
			display_board[current_board_position.Y * BOARD_WIDTH + current_board_position.X] = FULL_TILE_CHAR_INFO;
		}
	}
}

bool is_in_bounds(COORD position) {
	return (position.X >= 0)
		&& (position.X < BOARD_WIDTH)
		&& (position.Y >= 0)
		&& (position.Y < BOARD_HEIGHT);
}
