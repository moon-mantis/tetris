#pragma once

#include "board.h"

#include <Windows.h>
#include <stdbool.h>

/**
* Returns: the time in milliseconds.
*/
UINT64 get_absolute_time_in_ms();

/**
* Returns: whether the position is inside of the board.
*/
bool is_in_bounds(COORD position);
