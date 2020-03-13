#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    const char *src = argv[1];
    const char *dst = argv[2];

    // Try to open src file
    int fdesc_src = open(src, O_RDONLY);
    if(fdesc_src < 0) {
        printf("cpf: cannot stat '%s'\n", src);
        return -1;
    }

    // Read stat for src file to get file size
    struct stat stbuf;
    stat(src, &stbuf);

    char filebuf[stbuf.st_size];
    int src_read = read(fdesc_src, filebuf, stbuf.st_size);
    if(src_read < 0) {
        printf("cpf: file read error '%s'\n", src);
        return -1;
    }

    // Create new copied file with standard Linux perms
    int fdesc_dst = open(dst, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    write(fdesc_dst, filebuf, src_read);

    printf("cpf: copied file '%s' to '%s'\n", dst, src);
    return 0;
}