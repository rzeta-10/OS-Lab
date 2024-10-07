//CS22B1093
//ROHAN G

#include <stdio.h>
#include <stdlib.h>

int quantum, total_processes, switch_count = 0;
int first_response_time[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int system_time = 0;
float accumulated_wait_time = 0, accumulated_tat = 0;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    struct Process *next;
};

struct Queue {
    struct Process *front;
    struct Process *rear;
};

void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(struct Queue* q, int id, int arrival, int burst) {
    struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
    newProcess->id = id;
    newProcess->arrival = arrival;
    newProcess->burst = burst;
    newProcess->remaining = burst;
    newProcess->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newProcess;
        return;
    }
    q->rear->next = newProcess;
    q->rear = newProcess;
}

struct Process dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return (struct Process){-1, -1, -1, -1, NULL};
    }
    struct Process* temp = q->front;
    struct Process p = *temp;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return p;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}

int main() {
    struct Queue job_queue;
    initQueue(&job_queue);

    printf("Enter the number of processes: ");
    scanf("%d", &total_processes);
    
    int ids[total_processes], arrivals[total_processes], bursts[total_processes];
    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    
    for (int i = 0; i < total_processes; i++) {
        printf("Enter Process ID, Arrival time, and Burst time for process %d: ", i + 1);
        scanf("%d %d %d", &ids[i], &arrivals[i], &bursts[i]);
    }
    
    int process_index = 0, tat = 0, wt = 0;
    
    while (process_index < total_processes || !isQueueEmpty(&job_queue)) {
        if (!isQueueEmpty(&job_queue)) {
            system_time++;
            struct Process current_job = dequeue(&job_queue);
            
            if (first_response_time[current_job.id - 1] == -1)
                first_response_time[current_job.id - 1] = system_time - current_job.arrival;
            
            if (current_job.remaining <= quantum) {
                switch_count++;
                system_time += current_job.remaining;
                current_job.remaining = 0;
                
                while (process_index < total_processes && arrivals[process_index] <= system_time) {
                    enqueue(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
                    process_index++;
                }
                
                tat = system_time - current_job.arrival;
                wt = tat - bursts[current_job.id - 1];
                accumulated_tat += tat;
                accumulated_wait_time += wt;
                
                printf("PID: %d AT: %d BT: %d FT: %d TAT: %d WT: %d RT: %d\n", 
                       current_job.id, current_job.arrival, 
                       bursts[current_job.id - 1], system_time, 
                       tat, wt, first_response_time[current_job.id - 1]);
                
            } else {
                switch_count++;
                system_time += quantum;
                current_job.remaining -= quantum;
                
                while (process_index < total_processes && arrivals[process_index] <= system_time) {
                    enqueue(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
                    process_index++;
                }
                enqueue(&job_queue, current_job.id, current_job.arrival, current_job.remaining);
            }
            
        } else {
            if (arrivals[process_index] > system_time) {
                switch_count++;
                system_time = arrivals[process_index];
            }
            enqueue(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
            process_index++;
        }
    }
    
    float cpu_efficiency = (float)(system_time - (switch_count + 1)) / system_time;
    printf("\nNumber of context switches: %d\n", switch_count + 1);
    printf("\nCPU utilization: %.2f%%\n", cpu_efficiency * 100);
    printf("\nAverage turnaround time: %.2f\n", accumulated_tat / total_processes);
    printf("\nAverage waiting time: %.2f\n", accumulated_wait_time / total_processes);
    
    return 0;
}