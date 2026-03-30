#pragma once

#define ERROR_BUFFER_SIZE (256)

/**
* Convert the last Windows error to a string and print it.
*/
void print_last_error(const char* context);
