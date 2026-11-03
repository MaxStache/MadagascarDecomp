#ifndef DECOMPHELPERS_H
#define DECOMPHELPERS_H
#include <stdio.h>
#include <stdarg.h>

inline void DecompDebugPrint(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[LOG] ");
	vprintf(fmt, args);
	printf("\n");
	va_end(args);
	fflush(stdout);
}

#define DECOMP_DEBUG_PRINT DecompDebugPrint

#endif
