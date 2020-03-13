#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    const char *file = argv[1];

    // Try to get info about file
    struct stat file_stat;
    // lstat requires gnu99 instead of c99 (isn't compliant w/ ANSI standard)
    int stat_return = lstat(file, &file_stat);
    if(stat_return < 0) {
        printf("filat: cannot stat '%s'\n", file);
        return -1;
    }

    // Print header
    printf("-------------------");
    printf(" %s ", file);
    printf("------------------------\n");

    // Print file/device type
    printf("File type\t\t: ");
    switch (file_stat.st_mode & S_IFMT) {
        case S_IFREG:  
            puts("Regular file");
            break;
        case S_IFDIR:
            puts("Directory");
            break;
        case S_IFCHR:        
            puts("Character Device");
            break;
        case S_IFBLK:        
            puts("Block device");
            break;
        case S_IFLNK: 
            puts("Symlink");
            break;
        case S_IFIFO: 
            puts("Pipe");    
            break;
        case S_IFSOCK:
            puts("Socket");
            break;
        default:
            puts("? - Unknown"); 
    }

    // Print privileges
    printf("Access privileges\t: ");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    puts("");

    // Print other details
    printf("inode-Number\t\t: %ld\n", file_stat.st_ino);
    printf("Dev. numbers\t\t: dev = %ld; rdev = %ld\n", file_stat.st_dev, file_stat.st_rdev);
    printf("Links count\t\t: %ld\n", file_stat.st_nlink);
    printf("UID\t\t\t: %d\n", file_stat.st_uid);
    printf("GID\t\t\t: %d\n", file_stat.st_gid);
    printf("File size\t\t: %ld\n", file_stat.st_size);

    // Print date-times
    printf("Last access\t\t: %s", ctime(&file_stat.st_atime));
    printf("Last modification\t: %s", ctime(&file_stat.st_mtime));
    printf("Last inode change\t: %s", ctime(&file_stat.st_ctime));
}