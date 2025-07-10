#include<stdio.h>
#include<unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if(pid < 0) {
        printf("Error, Unable to create Child Process !!");
    }else if ( pid == 0) {
        printf("Child Process has successfully created !!\n");
        printf("PID of Child : %d\n",getpid());
        printf("PID of Parent : %d\n", getppid());
    }else {
        printf("Parent process created successfully !!\n");
        printf("PID of Parent : %d\n",getpid());
        printf("PID of Child created : %d\n",pid);
    }
    return 0;
}