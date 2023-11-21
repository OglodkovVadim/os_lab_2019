#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid = fork();

    if (pid > 0) {
        printf("Parent\n");
        return 0;
    }
    else if (pid == 0) {
        sleep(10000);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}