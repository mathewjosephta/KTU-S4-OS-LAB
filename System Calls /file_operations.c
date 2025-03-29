#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    char buf[14];

    // Create and write to file
    fd = open("myfile.txt", O_CREAT | O_WRONLY, 0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }

    if (write(fd, "hai world!\n", 13) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);

    // Read from file
    fd = open("myfile.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    if (read(fd, buf, 13) == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    buf[13] = '\0';  // Null-terminate the string

    close(fd);
    printf("%s\n", buf);

    return 0;
}
