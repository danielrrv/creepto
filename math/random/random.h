#ifndef CREEPTO_RANDOM_H
#define CREEPTO_RANDOM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

static void get_OS_entropy(uint8_t *in_out_bytes, int byte_size)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	BCryptGenRandom(NULL, in_out_bytes, byte_size, BCRYPT_USE_SYSTEM_PREFERRED_PTR);
#elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
	const int fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "No such file or directory: /dev/urandom\n");
		}
		return;
	}

	if (read(fd, in_out_bytes, byte_size) < 0)
	{
		fprintf(stderr, "Failed to read from /dev/urandom\n");
	}
	close(fd);
#endif
}

#endif