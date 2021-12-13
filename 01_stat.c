#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
//-----------------------------------------------------
#include "../funcs.h"

int main(int argc, char* argv[])
{
    struct stat sb;


    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1], &sb) == -1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);

    }  

    printf("            Name of file: %s   %s\n", argv[1], typeFile(sb.st_mode));
        
    printf("            Size of file: %ld\n", sb.st_size);
    printf("Recomended size of block: %ld\n", sb.st_blksize);
    printf("        Amount of blocks: %ld\n", sb.st_blocks);

    printf("                  Device: %lu, I-node: %lu, Links: %lu \n", sb.st_dev, sb.st_ino, sb.st_nlink);
    
    printf("                     Uid: %u\n", sb.st_uid);
    printf("                     Gid: %u\n", sb.st_gid);
    
    print_access(&sb);
    
    printf("             Last access: ");
    printf_time(&sb.st_atime);
    printf("        Last modifaction: ");
    printf_time(&sb.st_mtime);
    printf("             Last change: ");
    printf_time(&sb.st_ctime);

    exit(EXIT_SUCCESS);
}
