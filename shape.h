#pragma once

#include "board.h"

#include <Windows.h>
#include <stdbool.h>

#define BIGGEST_SHAPE_SIZE (4)

static const COORD SHAPE_STARTING_POSITION = { .X = BOARD_WIDTH / 2, .Y = 0 };

typedef struct {
	tile_state_t tiles[BIGGEST_SHAPE_SIZE * BIGGEST_SHAPE_SIZE];
	size_t size;
} shape_t;

static const shape_t SQUARE_SHAPE = { {
	1, 1,
	1, 1
}, 2u };

static const shape_t Z_SHAPE = { {
	0, 0, 0,
	1, 1, 0,
	0, 1, 1
}, 3u };

static const shape_t T_SHAPE = { {
	0, 1, 0,
	1, 1, 1,
	0, 0, 0
}, 3u };

static const shape_t LINE_SHAPE = { {
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0
}, 4u };

static const shape_t L_SHAPE = { {
	0, 0, 1,
	1, 1, 1,
	0, 0, 0
}, 3u };

static const shape_t Z_PRIME_SHAPE = { {
	0, 0, 0,
	0, 1, 1,
	1, 1, 0
}, 3u };

static const shape_t L_PRIME_SHAPE = { {
	1, 0, 0,
	1, 1, 1,
	0, 0, 0
}, 3u };

/**
* Generates a random shape.
* Uses the `rand()` function for randomness, so `srand()` should be called before this function.
* 
* Returns: a random shape.
*/
shape_t get_random_shape();

/**
* 
*/
shape_t rotate_shape_clockwise(shape_t shape);
