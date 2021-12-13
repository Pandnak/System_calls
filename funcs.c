#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>                
#include <sys/stat.h>
#include <time.h>
// --------------------------------------------------------------------------------------------
#include "funcs.h"


//function defines type of file
const char* typeFile(const mode_t mode)
{
    switch(mode & S_IFMT)
    {
        case S_IFBLK:  return "block device";         
        case S_IFCHR:  return "character device";    
        case S_IFDIR:  return "directory";          
        case S_IFIFO:  return "FIFO/pipe";         
        case S_IFLNK:  return "symlink";          
        case S_IFREG:  return "regular file";    
        case S_IFSOCK: return "socket";       
    }
    return "unknown?";    
}

//function print file access file
void print_access(const struct stat *sb)
{
    printf("                  Access:(%u/", sb -> st_mode);
	putchar( (sb->st_mode & S_IRUSR) ? 'r' : '-');
    putchar( (sb->st_mode & S_IWUSR) ? 'w' : '-');
   	putchar( (sb->st_mode & S_IXUSR) ? 'x' : '-');
   	putchar( (sb->st_mode & S_IRGRP) ? 'r' : '-');
   	putchar( (sb->st_mode & S_IWGRP) ? 'w' : '-');
  	putchar( (sb->st_mode & S_IXGRP) ? 'x' : '-');
  	putchar( (sb->st_mode & S_IROTH) ? 'r' : '-');
	putchar( (sb->st_mode & S_IWOTH) ? 'w' : '-');
    putchar( (sb->st_mode & S_IXOTH) ? 'x' : '-');
    printf(")\n");
}


void printf_time(const time_t *tmp)
{
     struct tm bdt;
     //char s[sizeof("DoW mmm dd hh:mm:ss yyyy")];   //DoW -- Day of the Week
     char s[sizeof("Mon Sep 20 21:56:40 2021")];
     ctime_r(tmp, s);
     localtime_r(tmp, &bdt);
     printf("%s %s", bdt.tm_zone, s);        
}




//function for writing all symbols to file and return count of writing bytes
ssize_t writeall(int fd, const void *buf, size_t count)
{
    size_t bytes_written = 0;
	const uint8_t *buf_addr = buf;
	while (bytes_written < count) 
    {
	    ssize_t res = write(fd, buf_addr + bytes_written, count - bytes_written);
        //write returns -1 on error, so we should check this case
        if(res < 0) 
        {
            return res;
        }
        bytes_written += (size_t)res;
    }
    return (ssize_t)bytes_written;
}
 
