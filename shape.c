#include "shape.h"
#include "board.h"
#include "utils.h"

#include <stdlib.h>

shape_t get_random_shape() {
	shape_t shape_options[] = {
		SQUARE_SHAPE,
		Z_SHAPE,
		T_SHAPE,
		LINE_SHAPE,
		L_SHAPE,
		Z_PRIME_SHAPE,
		L_PRIME_SHAPE,
	};

	size_t random_shape_index = (size_t)(rand() % (sizeof(shape_options) / sizeof(shape_t)));
	return shape_options[random_shape_index];
}

shape_t rotate_shape_clockwise(shape_t shape) {
	shape_t new_shape = shape;
	size_t new_x = 0, new_y = 0;

	for (size_t y = 0; y < shape.size; y++)
	{
		for (size_t x = 0; x < shape.size; x++)
		{
			new_x = (shape.size - 1u) - y;
			new_y = x;
			new_shape.tiles[new_y * shape.size + new_x] = shape.tiles[y * shape.size + x];
		}
	}

	return new_shape;
}
