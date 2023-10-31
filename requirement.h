/* Requirements of assignment */

#ifndef FCFS_SIM_REQUIREMENT_H
#define FCFS_SIM_REQUIREMENT_H

struct NODE
{
    int nodePid;
    int task;
    int arrivalTime;
    int workingTime;
    int waitTime;
    int returnTime;
    struct NODE* next;
};

#endif /* FCFS_SIM_REQUIREMENT_H */
