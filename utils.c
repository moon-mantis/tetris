#include "utils.h"

UINT64 get_absolute_time_in_ms() {
	static const UINT64 HUNDRED_NANOSECONDS_PER_MILLISECOND = 10000u;

	SYSTEMTIME system_time = { 0 };
	FILETIME absolute_filetime = { 0 };
	ULARGE_INTEGER absolute_time_in_100ns = { 0 };
	UINT64 absolute_time_in_ms = 0;

	GetSystemTime(&system_time);
	if (!SystemTimeToFileTime(&system_time, &absolute_filetime)) {
		print_last_error("getting absolute time in ms");
		return 0u;
	}

	absolute_time_in_100ns.LowPart = absolute_filetime.dwLowDateTime;
	absolute_time_in_100ns.HighPart = absolute_filetime.dwHighDateTime;

	absolute_time_in_ms = absolute_time_in_100ns.QuadPart / HUNDRED_NANOSECONDS_PER_MILLISECOND;
	return absolute_time_in_ms;
}

bool is_in_bounds(COORD position) {
	return (position.X >= 0)
		&& (position.X < BOARD_WIDTH)
		&& (position.Y >= 0)
		&& (position.Y < BOARD_HEIGHT);
}
