#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define PRINT_CLEAR_SEQUENCE() puts("\033[H\033[J")

static int shouldStop = 0;

void doTick() {
    while (getchar() != '\n');
}

int main() {
    while (!shouldStop) {
        PRINT_CLEAR_SEQUENCE();
        puts("FCFS simulator by Jisu Yu");
        doTick();
    }

    return 0;
}
