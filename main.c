#include <stdio.h>
#include <stdlib.h>
#include "requirement.h"
#include "list.h"

#define PRINT_CLEAR_SEQUENCE() puts("\033[H\033[J")

static int shouldStop = 0;

static struct NODE *taskListQueue, readyQueue, runQueue, terminatedQueue;

void doTick() {
    // Print all the tasks
    struct NODE *current = taskListQueue;
    while (current != NULL) {
        printf("PID: %d, TaskTime: %d, ArrivalTime: %d, WorkingTime: %d, WaitTime: %d, ReturnTime: %d\n",
               current->nodePid, current->task, current->arrivalTime,
               current->workingTime, current->waitTime, current->returnTime);
        current = current->next;
    }
    while (getchar() != '\n');
}

int main() {
    if (!initTasks(&taskListQueue, 10)) {
        perror("initTasks");
        exit(1);
    }

    while (!shouldStop) {
        PRINT_CLEAR_SEQUENCE();
        puts("FCFS simulator by Jisu Yu");
        doTick();
    }

    return 0;
}
