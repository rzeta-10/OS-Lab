#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    struct Process* next;
} Process;

Process* createProcess(int pid, int arrivalTime, int burstTime) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    newProcess->pid = pid;
    newProcess->arrivalTime = arrivalTime;
    newProcess->burstTime = burstTime;
    newProcess->completionTime = 0;
    newProcess->turnaroundTime = 0;
    newProcess->waitingTime = 0;
    newProcess->responseTime = 0;
    newProcess->next = NULL;
    return newProcess;
}

void insertProcess(Process** head, Process* newProcess) {
    if (*head == NULL || (*head)->burstTime > newProcess->burstTime) {
        newProcess->next = *head;
        *head = newProcess;
    } else {
        Process* current = *head;
        while (current->next != NULL && current->next->burstTime <= newProcess->burstTime) {
            current = current->next;
        }
        newProcess->next = current->next;
        current->next = newProcess;
    }
}

Process* extractMinProcess(Process** head) {
    if (*head == NULL) return NULL;
    Process* minProcess = *head;
    *head = (*head)->next;
    return minProcess;
}

void calculateSJF(Process processes[], int n) {
    Process* heap = NULL;
    int time = 0, completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process* scheduledOrder[n];
    int index = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].completionTime == 0) {
                insertProcess(&heap, &processes[i]);
                processes[i].completionTime = -1;  // Mark as added to heap
            }
        }

        if (heap == NULL) {
            time++;
            continue;
        }

        Process* currentProcess = extractMinProcess(&heap);

        if (currentProcess->responseTime == 0 && currentProcess->completionTime != -2) {
            currentProcess->responseTime = time - currentProcess->arrivalTime;
        }

        time += currentProcess->burstTime;
        currentProcess->completionTime = time;
        currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;

        totalWaitingTime += currentProcess->waitingTime;
        totalTurnaroundTime += currentProcess->turnaroundTime;
        scheduledOrder[index++] = currentProcess;
        completed++;
    }

    printf("PID   AT    BT    CT    TAT   WT    RT\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-6d%-6d%-6d%-6d%-6d%-6d%-6d\n",
               processes[i].pid, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime, processes[i].responseTime);
    }

    printf("Average waiting time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average turnaround time: %.2f\n", (float)totalTurnaroundTime / n);

    printf("Schedule:- ");
    for (int i = 0; i < n; i++) {
        printf("%d", scheduledOrder[i]->pid);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        int pid, arrivalTime, burstTime;
        printf("Enter process ID, Arrival Time, Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &pid, &arrivalTime, &burstTime);
        processes[i] = *createProcess(pid, arrivalTime, burstTime);
    }

    calculateSJF(processes, n);

    return 0;
}
