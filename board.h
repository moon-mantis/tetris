#pragma once

#define BOARD_WIDTH (10)
#define BOARD_HEIGHT (20)
#define BOARD_SIZE (BOARD_WIDTH * BOARD_HEIGHT)

typedef enum {
	EMPTY_TILE = 0, // allows zero initialization of empty board
	FULL_TILE
} tile_state_t;
