#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int totalWT = 0, totalTAT = 0;

struct Process {
    int P_ID;   // Process ID
    int AT;     // Arrival Time
    int BT;     // Burst Time
    int FT;     // Finish Time / Completion Time
    int TAT;    // Turnaround Time
    int WT;     // Wait Time
    int RT;     // Response Time
};

struct Node {
    struct Process data;
    struct Node* next;
};

struct minHeap {
    struct Node* left;
    struct Node* right;
};

void init(struct minHeap* q); // for initializing the process minHeap
void insert_process(struct minHeap* q, struct Process p); // inserting the processes into the minHeap
struct Process delete_process(struct minHeap* q); // deleting the process frim the minHeap
struct Process findShortestJob(struct minHeap* q, int currentTime); // finding the shortest job among the minHeap 
void calculateTimes(struct minHeap* q, int n); // calculating the respective time parameters
void printSchedule(struct minHeap* q, int n); // printing the final schedule
void getInput(struct minHeap* q, int* n); // getting the user input for each process

int main() {
    struct minHeap q;
    init(&q);

    int n;
    getInput(&q, &n);
    calculateTimes(&q, n);
    printSchedule(&q, n);

    return 0;
}

void init(struct minHeap* q) {
    q->left = q->right = NULL;
}

void insert_process(struct minHeap* q, struct Process p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = p;
    temp->next = NULL;

    if (q->right == NULL) {
        q->left = q->right = temp;
        return;
    }

    q->right->next = temp;
    q->right = temp;
}

struct Process delete_process(struct minHeap* q) {
    if (q->left == NULL) {
        printf("No more processes in the minHeap\n");
        exit(1);
    }

    struct Node* temp = q->left;
    struct Process p = temp->data;
    q->left = q->left->next;

    if (q->left == NULL) {
        q->right = NULL;
    }

    free(temp);
    return p;
}

struct Process findShortestJob(struct minHeap* q, int currentTime) {
    struct Node* temp = q->left;
    struct Process shortest = {0, 0, INT_MAX, 0, 0, 0, 0};
    struct Node* prev = NULL;
    struct Node* prevShortest = NULL;

    while (temp != NULL) {
        if (temp->data.AT <= currentTime && temp->data.BT < shortest.BT) {
            shortest = temp->data;
            prevShortest = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    if (shortest.BT == INT_MAX) {
        return shortest; 
    }

    if (prevShortest == NULL) {
        return delete_process(q);
    } else {
        struct Node* tempShortest = prevShortest->next;
        prevShortest->next = tempShortest->next;

        if (tempShortest == q->right) {
            q->right = prevShortest;
        }

        struct Process p = tempShortest->data;
        free(tempShortest);
        return p;
    }
}

void getInput(struct minHeap* q, int* n) {
    printf("Enter the number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        struct Process p;
        printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &p.P_ID, &p.AT, &p.BT);
        p.FT = p.TAT = p.WT = p.RT = 0;
        insert_process(q, p);
    }
}

void calculateTimes(struct minHeap* q, int n) {
    struct minHeap tempminHeap;
    init(&tempminHeap);

    int currentTime = 0;
    struct Process p;
    int completedProcesses = 0;
    //int totalWT = 0, totalTAT = 0;

    while (completedProcesses < n) {
        p = findShortestJob(q, currentTime);

        if (p.BT == INT_MAX) {
            currentTime++;
            continue;
        }

        if (currentTime < p.AT) {
            currentTime = p.AT;
        }

        p.RT = currentTime - p.AT;
        p.FT = currentTime + p.BT;
        p.TAT = p.FT - p.AT;
        p.WT = p.TAT - p.BT;
        currentTime = p.FT;
        
        totalWT += p.WT;
        totalTAT += p.TAT;

        insert_process(&tempminHeap, p);
        completedProcesses++;
    }

    // printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    // printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);

    *q = tempminHeap;
}

void printSchedule(struct minHeap* q, int n) {
    struct Node* temp = q->left;

    printf("\nSJF\n");
    printf("P_id  AT  BT  FT  TAT  WT  RT\n");

    while (temp != NULL) {
        struct Process p = temp->data;
        printf("%4d %4d %4d %4d %4d %4d %4d\n", p.P_ID, p.AT, p.BT, p.FT, p.TAT, p.WT, p.RT);
        temp = temp->next;
    }

    printf("\nSchedule: ");
    temp = q->left;
    while (temp != NULL) {
        printf("P%d ", temp->data.P_ID);
        temp = temp->next;
    }
    printf("\n");

    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
}