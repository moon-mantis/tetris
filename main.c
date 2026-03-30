#include "tetris.h"
#include "error.h"

#include <Windows.h>
#include <stdbool.h>

int main() {
	HANDLE screen_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == screen_handle) {
		print_last_error("opening handle to console");
		return 1;
	}

	// Make anything printed to the console appear below the game screen
	const COORD cursor_position = { .Y = BOARD_HEIGHT, .X = 0 };
	if (!SetConsoleCursorPosition(screen_handle, cursor_position)) {
		print_last_error("setting cursor position");
		return 1;
	}
	
	CONSOLE_CURSOR_INFO original_cursor_info;
	if (!GetConsoleCursorInfo(screen_handle, &original_cursor_info)) {
		print_last_error("getting cursor info");
		return 1;
	}

	const CONSOLE_CURSOR_INFO cursor_info = { .dwSize =
	original_cursor_info.dwSize, .bVisible = FALSE };
	if (!SetConsoleCursorInfo(screen_handle, &cursor_info)) {
		print_last_error("hiding blinking cursor");
		return 1;
	}

	bool successful = game_loop(screen_handle);
	// Restore original cursor
	if (!SetConsoleCursorInfo(screen_handle, &original_cursor_info)) {
		print_last_error("restoring cursor info");
		successful = false;
	}

	return successful ? 0 : 1;
}
