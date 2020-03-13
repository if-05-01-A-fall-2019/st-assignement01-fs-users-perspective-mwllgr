#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

// Prints the type for a file/dir
void print_file_type(struct stat attribs) {
    switch (attribs.st_mode & S_IFMT) {
        case S_IFBLK:  
            printf("b");
            break;
        case S_IFCHR:  
            printf("c");        
            break;
        case S_IFDIR:  
            printf("d");               
            break;
        case S_IFLNK:  
            printf("l");                 
            break;
        case S_IFSOCK: 
            printf("s");                  
            break;
        case S_IFREG:  
            printf("-");            
            break;
        case S_IFIFO:  
            printf("f");               
            break;
        default:       
            printf("-");                
            break;
        }
}

// Prints the access privileges
void print_acc_privs(struct stat attribs) {
    printf((attribs.st_mode & S_IRUSR) ? "r" : "-");
    printf((attribs.st_mode & S_IWUSR) ? "w" : "-");
    printf((attribs.st_mode & S_IXUSR) ? "x" : "-");
    printf((attribs.st_mode & S_IRGRP) ? "r" : "-");
    printf((attribs.st_mode & S_IWGRP) ? "w" : "-");
    printf((attribs.st_mode & S_IXGRP) ? "x" : "-");
    printf((attribs.st_mode & S_IROTH) ? "r" : "-");
    printf((attribs.st_mode & S_IWOTH) ? "w" : "-");
    printf((attribs.st_mode & S_IXOTH) ? "x" : "-");
}

int main(int argc, char const *argv[])
{
    char path[255];
    strcpy(path, ".");

    DIR* dir = opendir(path);
    struct dirent* dir_entry;
    struct stat dir_stat;

    while((dir_entry = readdir(dir))) {
        if(dir_entry->d_name[0] != '.') {
            strcpy(path, dir_entry->d_name);
            lstat(path, &dir_stat);
            
            print_file_type(dir_stat);
            print_acc_privs(dir_stat);

            printf("%5d", dir_stat.st_uid);
            printf(" %5d", dir_stat.st_gid);
            printf(" %9ld ", dir_stat.st_size);
            printf(" %s ", ctime(&dir_stat.st_mtime));
            printf("%s", dir_entry->d_name);
            puts("");
        }
    }
}