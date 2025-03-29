#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char file[100];
    struct stat nfile;

    printf("Enter the file name: ");
    scanf("%s", file);

    if (stat(file, &nfile) == -1) {
        perror("Error retrieving file info");
        return 1;
    }

    printf("Last access time: %ld\n", nfile.st_atime);
    printf("Inode number: %ld\n", nfile.st_ino);
    printf("Block size: %ld\n", nfile.st_blksize);
    printf("Access mode: %ld\n", nfile.st_mode);
    printf("User ID: %d\n", nfile.st_uid);

    return 0;
}

