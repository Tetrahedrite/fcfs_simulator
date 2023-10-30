#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define PRINT_CLEAR_SEQUENCE() puts("\033[H\033[J")

static int shouldStop = 0;

void signalHandler(int sig) {
    printf("\nGot signal: %d\n", sig);
    exit(1);
}

void doTick() {
    while (getchar() != '\n');
}

int main() {
    signal(SIGINT, signalHandler);
    puts("FCFS simulator by Jisu Yu");
    PRINT_CLEAR_SEQUENCE();

    while (!shouldStop)
        doTick();

    return 0;
}
