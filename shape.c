#include "shape.h"
#include "board.h"

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
