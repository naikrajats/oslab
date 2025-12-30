//Multiple child creation and execution using execl() - List Arguments with Full Path

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
	pid_t pid2 = fork();
	int status;
    
    if (pid1 == 0) {
        // Child process
        printf("First Child process with ID %d: About to execute '/bin/echo'\n",getpid());
        
        execl("/bin/echo", "echo", "Hello from execl!", NULL);
        
        // If execl fails
        perror("execl failed");
        return 1;
    }
    if (pid2 == 0) {
        // Child process
        printf("Second Child process with ID %d: About to execute '/bin/ls'\n",getpid());
        
        execl("/bin/ls", "ls", "-l", NULL);
        
        // If execl fails
        perror("execl failed");
        return 1;
    }	
        // Parent process
        wait(NULL);
		//waitpid(pid2,&Status,NULL);
        printf("Parent process: Child finished\n");
        
    return 0;
}