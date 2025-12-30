#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char message[100];

    // Create FIFO if it does not exist
    mkfifo(FIFO_NAME, 0666);

    // Open FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    printf("Enter a message to send: ");
    fgets(message, sizeof(message), stdin);

    // Write to FIFO
    write(fd, message, sizeof(message));

    close(fd);
    return 0;
}
