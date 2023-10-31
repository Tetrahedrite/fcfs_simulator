#include <stdio.h>
#include <stdlib.h>
#include "requirement.h"
#include "list.h"

#define PRINT_CLEAR_SEQUENCE() puts("\033[H\033[J")

static int shouldStop = 0;
static int tick = 0;

static struct NODE *taskListQueue, *readyQueue, *runQueue, *terminatedQueue;

void printTasks(struct NODE *taskList) {
    // Print all the taskList
    puts("Task List: ");
    while (taskList != NULL) {
        printf("  PID: %d, TaskTime: %d, ArrivalTime: %d, WorkingTime: %d, WaitTime: %d, ReturnTime: %d\n",
               taskList->nodePid, taskList->task, taskList->arrivalTime,
               taskList->workingTime, taskList->waitTime, taskList->returnTime);
        taskList = taskList->next;
    }
    fputs("\n", stdout);
}

void doTick() {
    // If ready queue is empty and current tick is greater than the arrival time of the first task in the task list...
    if (readyQueue == NULL && tick > taskListQueue->arrivalTime) {
        readyQueue = taskListQueue;
        taskListQueue = taskListQueue->next;
        readyQueue->next = NULL;
    }

    printTasks(taskListQueue);
    printTasks(readyQueue);
    printTasks(runQueue);
    printTasks(terminatedQueue);
    while (getchar() != '\n');
    tick++;
}

int main() {
    if (!initTasks(&taskListQueue, 10)) {
        perror("initTasks");
        exit(1);
    }

    while (!shouldStop) {
        PRINT_CLEAR_SEQUENCE();
        printf("FCFS simulator by Jisu Yu - Current tick: %d\n\n", tick);
        doTick();
    }

    return 0;
}
