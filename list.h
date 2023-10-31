#ifndef FCFS_SIM_LIST_H
#define FCFS_SIM_LIST_H

int initTasks(struct NODE** head, int count);
int randNumber();
void destroyTasks(struct NODE* head);
void insertSorted(struct NODE** head, struct NODE* newNode);

#endif /* FCFS_SIM_LIST_H */
