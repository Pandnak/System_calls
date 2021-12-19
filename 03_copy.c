// Программа читает информацию из одного файла и  записывает ее в другой файл.
// Сначала файл, откуда копируется, а потом файл, куда копируется.
#include <unistd.h> // for read
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//------------------------------------
#include "./funcs.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s \n", argv[0]);
        perror("Wrong number of arguments");
        return RESULT_BAD_ARG;
    }
    //opening descriptor with accesses: r/w for user and r only for group and others
    int fd = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, 0644);

    //check correct opening of descriptor
    if (fd < 0)
    {
        perror("File opening error");
        return RESULT_OPEN_FAILED;
    }

    if (read(fd, buf, count) < 0)
    {
        perror("File opening error");
        close(fd);
        return RESULT_BAD_READ;
    }



    

    //check correct closing of descriptor
    if (close(fd) < 0)
    {
        perror("File closing error");
        return RESULT_BAD_CLOSE;
    }

    return RESULT_OK;
}

