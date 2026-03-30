#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#include "error.h"

void print_last_error(const char* context)
{
	TCHAR error_buffer[ERROR_BUFFER_SIZE];

	const DWORD error_size = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, /* Format msg from the system */
		NULL, /* Message format - obtained from error code */
		GetLastError(), /* Message ID */
		0, /* Language neutral */
		error_buffer, /* Output buffer */
		sizeof(error_buffer) / sizeof(TCHAR), /* Output buffer size in TCHARs */
		NULL
	/* Arguments for the format string */);
	fprintf(stderr, "An error occurred while %s", context);
	if (0 != error_size) {
		_ftprintf(stderr, _T(": %s"), error_buffer);
	}
	fprintf(stderr, "\n");
}
