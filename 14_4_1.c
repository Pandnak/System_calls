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

#include "./funcs.h"

#define MAX_LEN 1000
const size_t count = 5; // number of  bytes are read for one cycle

int main(void) {
	unsigned long nbytes = 0;
	void *buf = malloc(MAX_LEN);

	FILE *ptrFile = fopen("stderr.txt", "wb");
	if (ptrFile == NULL) {
		perror("Wrong of file");
		return RESULT_OPEN_FAILED;
	}

	struct timespec tmStart; //Тут компилятор требовал инициализацию времен,
	struct timespec
		tmEnd; //хотя они все равно в них потом все равно записывается время
	// use clock_gettime
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmStart);

	// printf("%ld\n", (- (tmEnd.tv_nsec)  + tmStart.tv_nsec)%1000000000);
	while (1) {
		if (nbytes += (read(fileno(stdin), buf, count)) == 0) {
			if (ferror(stdin) != 0) {
				// printf("%lu\n", nbytes);
				fprintf(ptrFile, "%lu bytes read\n", nbytes);
				perror("Wrong reading stdin");
				free(buf);
				return RESULT_BAD_READ;
			}
			if (feof(stdin) != 0) {
				// printf("%lu\n", nbytes);
				fprintf(ptrFile, "%lu bytes read\n", nbytes);
				break;
			}
		}
		// printf("%lu\n", nbytes);
	}
	printf("%lu\n", nbytes);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmEnd);

	fprintf(
		ptrFile, "%ld.%06ld\n", (tmEnd.tv_nsec - tmStart.tv_nsec) / 1000000000,
		(tmEnd.tv_nsec - tmStart.tv_nsec) % 1000000000 / 1000); // nsec in long
	free(buf);
	fclose(ptrFile);
	return RESULT_OK;
}
