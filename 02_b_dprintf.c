// Программа получает на вход файл и строку. Эта строка записывается в файл. 
// Если такого файла не существует, то он будет создан и в него запишется строка.
#include <stdio.h>   // for perrror
#include <unistd.h>  // for close 
#include <string.h>
#include <stdint.h> // for uint8_t
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 
//---------------------------------------------------------
#include "./funcs.h"


/*
   size_t  ---- unsigned type
   ssize_t ---- signed type
   uint8_t ---- unsigned eight-bits int type of data
*/
int main(int argc, char* argv[])
{
    //check number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        perror("Wrong number of arguments");
        return RESULT_BAD_ARG;
    }   
    
    //opening descriptor with accesses: r/w for user and r only for group and others
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
     
    //check correct opening of descriptor
    if (fd < 0)
    {   
        perror("File opening error");
        return RESULT_OPEN_FAILED;
    }  
     
    //write string to file and check correct writing
    if (dprintf(fd,"%s", argv[2])  < 0) // return the number of characters printed, without \0.
    {                                   // return negative value in case of error
        perror("Failed write to file");
        close(fd);
        return RESULT_BAD_WRITE;
    }
     
    //check correct closing of descriptor
    if (close(fd) < 0)
    { 
		perror("File closing error");
		return RESULT_BAD_CLOSE;
	} 

	return RESULT_OK;
}
