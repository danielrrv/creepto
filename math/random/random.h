#ifndef CREEPTO_RANDOM_H
#define CREEPTO_RANDOM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

static void get_OS_entropy(uint8_t *in_out_bytes, int byte_size)
{
#if defined(_WIN32) || defined(__CYGWIN__)
    printf("on Windows\n");
#elif defined(__linux__)
    const int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
    {
        if (errno == ENOENT)
        {
            printf("No such file or directory\n");
        }
        return;
        // printf("%d\n",EACCES);
    }
    uint8_t buff[byte_size];
    // Read the content and print it
  
    if(read(fd, buff, byte_size) > 0){
        memcpy(in_out_bytes, buff, byte_size );
    }
    close(fd);
#elif defined(__APPLE__) && defined(__MACH__)
    printf("on MacOS\n");
#endif
}

#endif

// 1. read the system randomness source given the bytes.
// 2.