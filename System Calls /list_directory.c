#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    char path[100];
    DIR *dir;
    struct dirent *directory;

    printf("Enter the path: ");
    scanf("%s", path);

    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    while ((directory = readdir(dir)) != NULL) {
        printf("Inode: %lu\n", directory->d_ino);
        printf("Name: %s\n\n", directory->d_name);
    }

    closedir(dir);
    return 0;
}
