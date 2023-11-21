#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid = fork();

    if (pid > 0) {
        printf("Parent");
        wait(NULL);
    }
    else if (pid == 0) {
        execl("./sequential_min_max", "./sequential_min_max", "3", "3", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}