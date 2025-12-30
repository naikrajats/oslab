//Single child creation and execution using execv() - Full Path Required

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute '/bin/date'\n");
        
        char *args[] = {"date", NULL};
        execv("/bin/date", args);
        
        // If execv fails
        perror("execv failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}