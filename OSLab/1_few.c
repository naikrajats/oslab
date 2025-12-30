1. execvp() - Most Common

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute 'ls -l'\n");
        
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        
        // If execvp fails
        perror("execvp failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}
2. execlp() - List Arguments

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute 'ps aux'\n");
        
        execlp("ps", "ps", "aux", NULL);
        
        // If execlp fails
        perror("execlp failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}
3. execv() - Full Path Required

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
4. execl() - List Arguments with Full Path

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute '/bin/echo'\n");
        
        execl("/bin/echo", "echo", "Hello from execl!", NULL);
        
        // If execl fails
        perror("execl failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}
5. execve() - With Environment Variables

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute '/usr/bin/env'\n");
        
        char *args[] = {"env", NULL};
        char *env[] = {
            "PATH=/usr/bin:/bin",
            "HOME=/home/user",
            "CUSTOM_VAR=HelloWorld",
            NULL
        };
        
        execve("/usr/bin/env", args, env);
        
        // If execve fails
        perror("execve failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}
6. execle() - List Arguments with Environment

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute '/bin/bash'\n");
        
        char *env[] = {
            "PATH=/usr/bin:/bin",
            "MY_VARIABLE=CustomValue",
            NULL
        };
        
        execle("/bin/bash", "bash", "-c", "echo $MY_VARIABLE", NULL, env);
        
        // If execle fails
        perror("execle failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Child finished\n");
    }
    
    return 0;
}
7. Combined Demo - All Functions

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void demo_execvp() {
    printf("\n=== execvp Demo ===\n");
    pid_t pid = fork();
    
    if (pid == 0) {
        char *args[] = {"ls", "-la", NULL};
        execvp("ls", args);
        perror("execvp");
        _exit(1);
    }
    wait(NULL);
}

void demo_execlp() {
    printf("\n=== execlp Demo ===\n");
    pid_t pid = fork();
    
    if (pid == 0) {
        execlp("pwd", "pwd", NULL);
        perror("execlp");
        _exit(1);
    }
    wait(NULL);
}

void demo_execv() {
    printf("\n=== execv Demo ===\n");
    pid_t pid = fork();
    
    if (pid == 0) {
        char *args[] = {"uname", "-a", NULL};
        execv("/bin/uname", args);
        perror("execv");
        _exit(1);
    }
    wait(NULL);
}

void demo_execl() {
    printf("\n=== execl Demo ===\n");
    pid_t pid = fork();
    
    if (pid == 0) {
        execl("/bin/echo", "echo", "Hello from execl!", NULL);
        perror("execl");
        _exit(1);
    }
    wait(NULL);
}

int main() {
    printf("Demonstrating different exec functions:\n");
    
    demo_execvp();
    demo_execlp();
    demo_execv();
    demo_execl();
    
    printf("\nAll demonstrations completed!\n");
    return 0;
}
