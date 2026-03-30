#pragma once

#include "board.h"
#include "shape.h"

#include <Windows.h>
#include <stdbool.h>

#define AUTOMATIC_DROP_TIME (1000)

typedef struct {
	tile_state_t board[BOARD_SIZE];
	shape_t current_shape;
	COORD current_shape_position;
	UINT64 time_since_last_drop;
} tetris_game_t;

enum key_presses {
	QUIT_KEY = 'q',
	LEFT_KEY = 'a',
	RIGHT_KEY = 'd',
	DOWN_KEY = 's'
};

static const COORD OFFSET_LEFT = { .X = -1, .Y = 0 };
static const COORD OFFSET_RIGHT = { .X = 1, .Y = 0 };
static const COORD OFFSET_DOWN = { .X = 0, .Y = 1 };

/**
* Run the game in a loop until it ends or the user quits.
* 
* Returns: whether the game ran successfuly or not.
*/
bool game_loop(HANDLE screen_handle);

/**
* Handle keyboard input from the user if it exists.
* 
* Returns: whether the user quit the game or not.
*/
bool handle_input(tetris_game_t* game);

/**
* Move the current shape based on the given offset if the move wouldn't cause the shape to be out of bounds,
* or overlapping a non-empty board tile.
* 
* Returns: whether the move was successfully performed or not.
*/
bool try_moving_shape(tetris_game_t* game, COORD offset);

/**
* Returns: true if the current shape is in bounds and not overlapping a non-empty board tile, false otherwise.
*/
bool is_shape_in_legal_position(tetris_game_t game);

/**
* Handle consequences of time passing in the game.
* 
* Returns: whether the player lost or not.
*/
bool handle_delta_time(tetris_game_t* game, UINT64 delta_time);
