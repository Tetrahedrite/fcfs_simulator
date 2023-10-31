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
    while (taskList != NULL) {
        printf("  PID: %d, TaskTime: %d, ArrivalTime: %d, WorkingTime: %d, WaitTime: %d, ReturnTime: %d\n",
               taskList->nodePid, taskList->task, taskList->arrivalTime,
               taskList->workingTime, taskList->waitTime, taskList->returnTime);
        taskList = taskList->next;
    }
    fputs("\n", stdout);
}

void doTick() {
    // Increase running task working time
    if (runQueue != NULL)
        runQueue->workingTime++;

    // Terminate if run task working time is greater than the working time
    if (runQueue != NULL && runQueue->workingTime >= runQueue->task) {
        runQueue->returnTime = tick;
        insertToLast(&terminatedQueue, runQueue);
        runQueue = NULL;
    }

    // Increase ready task wait time
    struct NODE *readyTask = readyQueue;
    while (readyTask != NULL) {
        readyTask->waitTime++;
        readyTask = readyTask->next;
    }

    // If ready queue is empty and current tick is greater than the arrival time of the first task in the task list...
    while (taskListQueue != NULL && tick >= taskListQueue->arrivalTime) {
        struct NODE *temp = taskListQueue->next;
        insertToLast(&readyQueue, taskListQueue);
        taskListQueue = temp;
    }

    // Execute the first ready task
    if (readyQueue != NULL && runQueue == NULL) {
        runQueue = readyQueue;
        readyQueue = readyQueue->next;
        runQueue->next = NULL;
    }

    if (taskListQueue == NULL && runQueue == NULL && readyQueue == NULL)
        shouldStop = 1;

    puts("Task List Queue: ");
    printTasks(taskListQueue);
    puts("Ready Queue: ");
    printTasks(readyQueue);
    puts("Run Queue: ");
    printTasks(runQueue);
    puts("Terminated Queue: ");
    printTasks(terminatedQueue);

    while (getchar() != '\n');
    tick++;
}

void printStatistics() {
    unsigned int taskCount = 0, totalWaitingTime = 0;
    double averageWaitingTime;
    while (terminatedQueue != NULL) {
        taskCount++;
        totalWaitingTime += terminatedQueue->waitTime;
        terminatedQueue = terminatedQueue->next;
    }
    averageWaitingTime = (double)totalWaitingTime / taskCount;

    printf("Total Tasks : %u\n", taskCount);
    printf("Total Waiting Time : %u\n", totalWaitingTime);
    printf("Average Waiting Time : %.2lf\n", averageWaitingTime);
}

int main() {
    if (!initTasks(&taskListQueue, randNumber())) {
        perror("initTasks");
        exit(1);
    }

    while (!shouldStop) {
        PRINT_CLEAR_SEQUENCE();
        printf("FCFS simulator by Jisu Yu - Current tick: %d\n\n", tick);
        doTick();
    }

    printStatistics();
    destroyTasks(terminatedQueue);

    return 0;
}
