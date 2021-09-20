#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<time.h>

const char* typeFile(const mode_t mode)
{
    switch(mode & S_IFMT)
    {
        case S_IFBLK:  return "block device";         break;
        case S_IFCHR:  return "character device";     break;
        case S_IFDIR:  return "directory";            break;
        case S_IFIFO:  return "FIFO/pipe";            break;
        case S_IFLNK:  return "symlink";              break;
        case S_IFREG:  return "regular file";         break;
        case S_IFSOCK: return "socket";               break;
        default:       return "unknown?";             break;
    }
}

void print_access(const struct stat *sb)
{
    printf("                  Access:(%u/", sb -> st_mode);
	putchar( (S_ISDIR(sb->st_mode)) ? 'd' : '-');
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
     char s[50];
     ctime_r(tmp, s);
     localtime_r(tmp, &bdt);
     printf("%s %s", bdt.tm_zone, s);        
}

int main(int argc, char* argv[])
{
    unsigned int fd;
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
    
    fd = open(argv[1], O_RDONLY);

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

    printf("         File descriptor: %d\n", fd);
    exit(EXIT_SUCCESS);
}
