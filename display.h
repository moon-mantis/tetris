#pragma once

#include "tetris.h"
#include "shape.h"
#include "board.h"

#include <Windows.h>

static const COORD BOARD_DIMENSIONS = { .X = BOARD_WIDTH, .Y = BOARD_HEIGHT };
static const SMALL_RECT BOARD_WRITE_REGION = {
	.Left = 0,
	.Right = BOARD_WIDTH - 1,
	.Top = 0,
	.Bottom = BOARD_HEIGHT - 1
};
static const COORD ORIGIN = { .X = 0, .Y = 0 };

static const CHAR_INFO EMPTY_TILE_CHAR_INFO = {
	.Char.UnicodeChar = '*',
	.Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
};
static const CHAR_INFO FULL_TILE_CHAR_INFO = {
	.Char.UnicodeChar = '#',
	.Attributes = FOREGROUND_RED
};

/**
* Renders and prints the game to the screen.
* 
* Returns: a nonzero value on success, or 0 on failure.
*/
BOOL render_and_display_game(HANDLE screen_handle, tetris_game_t game);

/**
* For each tile in the game board, converts it into a pixel and puts it in the character board.
*/
void render_board(CHAR_INFO character_board[BOARD_SIZE], const tile_state_t game_board[BOARD_SIZE]);

/**
* For each non-empty tile in the shape, if it's in bounds, and if it isn't on a non-empty character in
* the character board, converts it into a pixel and puts it in the character board.
*/
void render_shape(CHAR_INFO display_board[BOARD_SIZE], shape_t shape, COORD shape_position);

/**
* Returns whether the position is inside of the board or not.
*/
bool is_in_bounds(COORD position);
