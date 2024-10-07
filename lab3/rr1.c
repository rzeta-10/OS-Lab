//CS22B1093
//ROHAN G

#include <stdio.h>
#include <stdlib.h>

int quantum, total_processes, switch_count = 0;
int first_response_time[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int system_time = 0;
float accumulated_wait_time = 0, accumulated_tat = 0;

struct Job {
    int id;
    int arrival;
    int burst;
    int remaining;
    struct Job *prev;
    struct Job *next;
};

struct Job* createJob(int id, int arrival, int burst) {
    struct Job *newJob = (struct Job*)malloc(sizeof(struct Job));
    newJob->id = id;
    newJob->arrival = arrival;
    newJob->burst = burst;
    newJob->remaining = burst;
    newJob->prev = NULL;
    newJob->next = NULL;
    return newJob;
}

void enqueueJob(struct Job **queue, int id, int arrival, int burst) {
    struct Job *newJob = createJob(id, arrival, burst);
    if (*queue == NULL)
        *queue = newJob;
    else {
        struct Job *current = *queue;
        while (current->next != NULL)
            current = current->next;
        current->next = newJob;
        newJob->prev = current;
    }
}

struct Job* dequeueJob(struct Job **queue) {
    if (*queue == NULL) {
        printf("Queue is empty\n");
        return NULL;
    } else {
        struct Job *temp = *queue;
        *queue = (*queue)->next;
        if (*queue != NULL)
            (*queue)->prev = NULL;
        return temp;
    }
}

int main() {
    struct Job *job_queue = NULL;
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
    
    while (process_index < total_processes || job_queue != NULL) {
        if (job_queue != NULL) {
            system_time++;
            struct Job *current_job = dequeueJob(&job_queue);
            
            if (first_response_time[current_job->id - 1] == -1)
                first_response_time[current_job->id - 1] = system_time - current_job->arrival;
            
            if (current_job->remaining <= quantum) {
                switch_count++;
                system_time += current_job->remaining;
                current_job->remaining = 0;
                
                while (process_index < total_processes && arrivals[process_index] <= system_time) {
                    enqueueJob(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
                    process_index++;
                }
                
                tat = system_time - current_job->arrival;
                wt = tat - bursts[current_job->id - 1];
                accumulated_tat += tat;
                accumulated_wait_time += wt;
                
                printf("PID: %d AT: %d BT: %d FT: %d TAT: %d WT: %d RT: %d\n", 
                       current_job->id, current_job->arrival, 
                       bursts[current_job->id - 1], system_time, 
                       tat, wt, first_response_time[current_job->id - 1]);
                
            } else {
                switch_count++;
                system_time += quantum;
                current_job->remaining -= quantum;
                
                while (process_index < total_processes && arrivals[process_index] <= system_time) {
                    enqueueJob(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
                    process_index++;
                }
                enqueueJob(&job_queue, current_job->id, current_job->arrival, current_job->remaining);
            }
            
        } else {
            if (arrivals[process_index] > system_time) {
                switch_count++;
                system_time = arrivals[process_index];
            }
            enqueueJob(&job_queue, ids[process_index], arrivals[process_index], bursts[process_index]);
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