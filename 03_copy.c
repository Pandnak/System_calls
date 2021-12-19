// Программа читает информацию из одного файла и  записывает ее в другой файл.
// Сначала файл, откуда копируется, а потом файл, куда копируется.
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // for read
//------------------------------------
#include "./funcs.h"

const unsigned int MAX_LEN = 1024 * 1024; // 1 Mbyte

int main(int argc, char *argv[]) 
{
    //Check number of args
	if (argc != 3) 
    {
		fprintf(stderr, "Usage: %s \n", argv[0]);
		perror("Wrong number of arguments");
		return RESULT_BAD_ARG;
	}
    
    //Getting info about source file
    struct stat sb;                      // structure for info about file
    if (lstat(argv[1], &sb) == -1)
    {
        perror("lstat");
        return RESULT_BAD_STAT;
    }
    
    //Check type of reading file
    if ((sb.st_mode & S_IFMT) != S_IFREG) 
    {
        perror("It isn't regular file. Denied");
        return RESULT_BAD_FILE_TYPE;
    }

    //Getting fd of source and destination files
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd < 0)
    {
        perror("File hasn't opened");
        return RESULT_OPEN_FAILED;
    }
    int dest_fd = open(argv[2], O_WRONLY, O_CREAT, O_TRUNC, 0644);
    if (dest_fd < 0)
    {
        perror("File hasn't opened");
        return RESULT_OPEN_FAILED;
    }

    //Check rights of source file
    if ((sb.st_mode & S_IRUSR) != 1)
    {
        perror("Not enough rights to read");
        return RESULT_ERR;
    }

    long size_source = sb.st_size;

    //Check rights of dest file
    if (lstat(argv[2], &sb) == -1)
    {
        perror("lstat");
        return RESULT_BAD_STAT;
    }
    
    if ((sb.st_mode & S_IWUSR) == -1)
    {
        perror("Not enough rights to write");
        return RESULT_ERR;
    }

    my_copy_files(source_fd, dest_fd, argv[2], size_source , max_len);

    //Closing files
    if (close(source_fd) < 0) 
    {
        perror("Source file closing error");
        return RESULT_BAD_CLOSE;
    }

    if (close(dest_fd) < 0) 
    {
        perror("Destination file closing error");
        return RESULT_BAD_CLOSE;
    }
    return RESULT_OK;
}
