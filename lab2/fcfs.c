// assuming arrival time is in increasing order

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int P_ID;   //process_id
    int AT;     //arrival time
    int BT;     //burst time
    int FT;     //finish time / completion time
    int TAT;    //turn around time
    int WT;     //wait time
    int RT;     //response time
};

struct Node {
    struct Process data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

void initQueue(struct Queue* q); //for inintializing the process queue
void enqueue(struct Queue* q, struct Process p); // adding the processes to the queue
struct Process dequeue(struct Queue* q); // removing the processes once they are completed
void calculateTimes(struct Queue* q, int n); // calculating the respective time based parameters
void printSchedule(struct Queue* q, int n); // printing the final schedule 
void getInput(struct Queue* q, int* n); // getting user input for each process

int main() {
    struct Queue q;
    initQueue(&q);
    
    int n;
    getInput(&q, &n);
    calculateTimes(&q, n);
    printSchedule(&q, n);
    
    return 0;
}

void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(struct Queue* q, struct Process p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = p;
    temp->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    
    q->rear->next = temp;
    q->rear = temp;
}

struct Process dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("No more processes in the queue\n");
        exit(1);
    }
    
    struct Node* temp = q->front;
    struct Process p = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return p;
}

void getInput(struct Queue* q, int* n) {
    printf("Enter the number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        struct Process p;
        printf("Enter Process ID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &p.P_ID, &p.AT, &p.BT);
        p.FT = p.TAT = p.WT = p.RT = 0;
        enqueue(q, p);
    }
}

void calculateTimes(struct Queue* q, int n) {
    struct Queue tempQueue;
    initQueue(&tempQueue);

    int currentTime = 0;
    struct Process p;

    for (int i = 0; i < n; i++) {
        p = dequeue(q);
        
        if (currentTime < p.AT) {
            currentTime = p.AT;
        }
        
        p.RT = currentTime - p.AT;
        p.FT = currentTime + p.BT;
        p.TAT = p.FT - p.AT;
        p.WT = p.TAT - p.BT;
        currentTime = p.FT;
        
        enqueue(&tempQueue, p);
    }

    *q = tempQueue;
}

void printSchedule(struct Queue* q, int n) {
    struct Node* temp = q->front;
    int totalWT = 0, totalTAT = 0;

    printf("\nFCFS\n");
    printf("P_id  AT  BT  FT  TAT  WT  RT\n");

    while (temp != NULL) {
        struct Process p = temp->data;
        printf("%4d %4d %4d %4d %4d %4d %4d\n", p.P_ID, p.AT, p.BT, p.FT, p.TAT, p.WT, p.RT);
        totalWT += p.WT;
        totalTAT += p.TAT;
        temp = temp->next;
    }

    printf("\nAvg waiting time: %.2f\n", (float)totalWT / n);
    printf("Avg turnaround time: %.2f\n", (float)totalTAT / n);

    printf("\nSchedule: ");
    temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data.P_ID);
        temp = temp->next;
    }
    printf("\n");
}