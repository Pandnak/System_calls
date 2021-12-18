// Программа получает на вход файл и строку. Эта строка записывается в файл. 
// Если такого файла не существует, то ничего не происходит.
#include <stdio.h>   // for perrror
#include <unistd.h>  // for write 
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
        return 1;
    }   
    
    //opening descriptor with accesses: r/w for user and r only for group and others
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
     
    //check correct opening of descriptor
    if (fd < 0)
    {   
        perror("File opening error");
        return 1;
    }  
     
    //write string to file and check correct writing
    if (writeall(fd, argv[2], strlen(argv[2])) < 0)
    {   
        perror("Failed write to file");
        close(fd);
        return 3;
    }
     
    //check correct closing of descriptor
    if (close(fd) < 0)
    { 
		perror("File closing error");
		return 4;
	} 

	return 0;
}
