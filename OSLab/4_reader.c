#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char buffer[100];

    // Create FIFO if not exists
    mkfifo(FIFO_NAME, 0666);

    // Open FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Read data
    read(fd, buffer, sizeof(buffer));

    printf("Received message: %s\n", buffer);

    close(fd);
    return 0;
}
