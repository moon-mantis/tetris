#pragma once

#include "board.h"

#include <Windows.h>
#include <stdbool.h>

typedef struct {
	tile_state_t board[BOARD_SIZE];
} tetris_game_t;

/**
* Run the game in a loop until it ends or the user quits.
* 
* Returns: whether the game ran successfuly or not.
*/
bool game_loop(HANDLE screen_handle);
