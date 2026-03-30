#include "display.h"

BOOL render_and_print_game(HANDLE screen_handle, tetris_game_t game) {
	CHAR_INFO character_board[BOARD_SIZE] = { 0 };
	static const COORD BOARD_DIMENSIONS = { .X = BOARD_WIDTH, .Y = BOARD_HEIGHT };
	SMALL_RECT write_region = BOARD_WRITE_REGION;

	render_board(character_board, game.board);

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
