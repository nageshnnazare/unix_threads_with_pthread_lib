#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

int x = 2;

void* routine() {
    x += 5;
    sleep(2);
    printf("Value of x(T1): %d\n", x);
}

void* routine2() {
    sleep(2);
    printf("Value of x(T2): %d\n", x);
}

int process_fork() {
    int x = 2;
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    
    if (pid == 0) {
        x++;
    }
    sleep(2);
    if (pid == 0) {
        printf("Value of x(Child): %d\n", x);
    }
    else {
        printf("Value of x(Parent): %d\n", x);
    }

    if (pid != 0) {
        wait(NULL);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    process_fork();
    
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL)) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL)) {
        return 2;
    }
    if (pthread_join(t1, NULL)) {
        return 3;
    }
    if (pthread_join(t2, NULL)) {
        return 3;
    }
    return 0;
}