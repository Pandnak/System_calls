#include <fcntl.h>
#include <stdint.h> // for uint8_t
#include <stdio.h>
#include <stdio.h> // for perrror
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>	//for clock_gettime
#include <unistd.h> // for write
#include <errno.h>

#include "./funcs.h"

#define MAX_LEN 1024
const size_t count = 16; // number of  bytes are read for one cycle

int main(void) 
{
	char buf[MAX_LEN];
    ssize_t nbytes= 0, numb;

	struct timespec tmStart; //Тут компилятор требовал инициализацию времен,
    struct timespec tmEnd; //хотя они все равно в них потом все равно записывается время
	// use clock_gettime
	if (clock_gettime(CLOCK_MONOTONIC, &tmStart) < 0)
    {
        perror("Error clock gettime");
        return RESULT_ERR;
    }

	while (1) 
    {
		if ((numb = read(fileno(stdin), buf, count)) <= 0) 
        {
			if (numb <  0) 
            {
				fprintf(stderr, "%lu bytes read\n", nbytes);
				perror("Wrong reading stdin");
				return RESULT_BAD_READ;
			}
			if (numb == 0) 
            {
				fprintf(stderr, "%lu bytes read\n", nbytes);
				break;
			}
		}
        nbytes += numb;
	}

	if (clock_gettime(CLOCK_MONOTONIC, &tmEnd) < 0)
    {
        perror("Error clock gettime");
        return RESULT_ERR;
    }

    if (tmEnd.tv_nsec - tmStart.tv_nsec >= 0)
    {
        fprintf(stderr, "Program execution time: %ld.%09ld\n", (tmEnd.tv_sec - tmStart.tv_sec),
		                                (tmEnd.tv_nsec - tmStart.tv_nsec)); // nsec in long
    }
    else
    {
        fprintf(stderr, "Program execution time: %ld.%09ld\n", (tmEnd.tv_sec - tmStart.tv_sec - 1), (tmEnd.tv_nsec - tmStart.tv_nsec) + 10000000000); // nsec in long
    }
	return RESULT_OK;
}
