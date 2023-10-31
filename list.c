#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "requirement.h"
#include "list.h"

int initTasks(struct NODE **head, int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        struct NODE *newNode = (struct NODE *) calloc(sizeof(struct NODE), 1);
        assert(newNode != NULL);
        newNode->nodePid = i + 1;
        newNode->task = randNumber();
        newNode->arrivalTime = randNumber();
        insertSorted(head, newNode);
    }

    return 1;
}

int randNumber() {
    return rand() % 10;
}

void destroyTasks(struct NODE *head) {
    while (head != NULL) {
        struct NODE *temp = head;
        head = head->next;
        free(temp);
    }
}

void insertSorted(struct NODE **head, struct NODE *newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct NODE *temp = *head;
    struct NODE *prev = *head;

    // temp가 NULL이 아니고 새로운 노드가 기존 노드보다 크면
    while (temp != NULL && temp->arrivalTime < newNode->arrivalTime) {
        prev = temp; // prev에 이전 노드 저장
        temp = temp->next; // temp가 다음 노드로 이동
    }

    // 가장 작으면 왼쪽에 끼워넣고, 그렇지 않으면 이전 노드와 현재 노드 사이에 연결
    if (temp == *head) { // temp가 head 그대로면 (== 현재 값이 가장 작음)
        newNode->next = *head; // 새로운 노드의 다음 노드를 head로 설정
        *head = newNode; // head를 새로운 노드로 설정
    } else { // 그렇지 않으면...
        newNode->next = prev->next; // 새로운 노드의 다음 노드를 prev의 다음 노드로 설정
        prev->next = newNode; // prev의 다음 노드를 새로운 노드로 설정
    }
}
