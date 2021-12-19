#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>                
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
// --------------------------------------------------------------------------------------------
#include "./funcs.h"


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

// the function of the removing fire from the current dir
int rm_file(const char* filename) {

    if (unlink(filename) == -1) {
        perror("It's not possible to remove this file");
        return RESULT_ERR;
    }
    printf("[+] Successful removing: %s", filename);
    return RESULT_OK;
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

int my_copy_files(unsigned source_fd, unsigned dest_fd, const char* dest_name, long long size_source, const unsigned max_len)
{
     // Make buffer for copy after
    char* buf = (char*) calloc(max_len, sizeof(char));
    assert(buf != NULL);

    //Copy
    while(size_source  > 0) 
    {

        ssize_t read_symb_amount = read(source_fd, buf, max_len);

        if (read_symb_amount < 0) 
        {
            perror("Failed read from the file");
            rm_file(dest_name);
            close(source_fd);
            return RESULT_BAD_READ;
        }

        ssize_t write_symb_amount = writeall(dest_fd, buf, read_symb_amount);

        if (write_symb_amount < 0) 
        {
            perror("Failed write to file");
            rm_file(dest_name);
            close(dest_fd);
            return RESULT_BAD_WRITE;
        }

        if (write_symb_amount != read_symb_amount) 
        {
            perror("The number of symbols written does't match the number of symbols read.");
            rm_file(dest_name);
            close(dest_fd);
            return RESULT_BAD_WRITE;
        }

        size_source -= read_symb_amount;
    }

    free(buf);

    return RESULT_OK;
} 
