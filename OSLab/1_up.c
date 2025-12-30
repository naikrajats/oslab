//Child executing user program
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: About to execute '/bin/echo'\n");
        
        execl("/usr/myprog", "myprog", NULL);
        
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

/*
//myprog.c

#include<stdio.h>
int main(){
	int i;
	for(i=0;i<=10;i++)
		printf("%d\t",i+1);
	printf("\n");
	return 0;
}

Save this as a seperate file and compile this program using cc myprog.c -o myprog
*/