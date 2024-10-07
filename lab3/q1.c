//CS22B1093
//ROHAN G

#include <stdio.h>
#include <stdlib.h>

int curr_time = 0;
int *exec_order;
int num_tasks = 0;
int exec_idx = 0;
int cap = 3;

struct Task {
    int id;
    int arrival;
    int prio;
    int burst;
    int comp;
    int tat;
    int wait;
    int resp;
    int done;
};

void show_exec_order(struct Task *tasks) {
    printf("\nExecution Order for Non-Preemptive Priority Scheduling:\n");
    for (int i = 0; i < exec_idx; i++) {
        printf("P%d ", tasks[exec_order[i]].id);
    }
    printf("\n");
}

void show_metrics(struct Task *tasks) {
    double total_tat = 0, total_wait = 0, total_resp = 0;
    printf("\nPID  Arr  PR  BT  CT  TAT  WT  RT\n");
    for (int i = 0; i < exec_idx; i++) {
        struct Task t = tasks[exec_order[i]];
        total_tat += t.tat;
        total_wait += t.wait;
        total_resp += t.resp;
        printf("%3d  %3d  %3d  %3d  %4d  %3d  %4d  %4d\n",
               t.id, t.arrival, t.prio, t.burst, t.comp,
               t.tat, t.wait, t.resp);
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / num_tasks);
    printf("Average Waiting Time: %.2f\n", total_wait / num_tasks);
    printf("Average Response Time: %.2f\n", total_resp / num_tasks);
}

void schedule_task(struct Task *tasks) {
    int min_prio = 100;
    int sel_task = -1;
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].done == 1 || tasks[i].arrival > curr_time) {
            continue;
        }
        if (tasks[i].prio < min_prio || 
            (tasks[i].prio == min_prio && tasks[i].arrival < tasks[sel_task].arrival)) {
            min_prio = tasks[i].prio;
            sel_task = i;
        }
    }
    if (sel_task != -1) {
        tasks[sel_task].comp = curr_time + tasks[sel_task].burst;
        tasks[sel_task].tat = tasks[sel_task].comp - tasks[sel_task].arrival;
        tasks[sel_task].wait = tasks[sel_task].tat - tasks[sel_task].burst;
        tasks[sel_task].resp = curr_time - tasks[sel_task].arrival;
        curr_time += tasks[sel_task].burst;
        exec_order[exec_idx++] = sel_task;
        tasks[sel_task].done = 1;
    }
}

int main() {
    struct Task *tasks = (struct Task *)malloc(cap * sizeof(struct Task));
    exec_order = (int *)malloc(100 * sizeof(int));

    while (1) {
        printf("Current Proc Time = %d\n", curr_time);
        int new_tasks;
        printf("Enter number of new tasks arriving with AT <= Current_Proc_time or -1 to finish: ");
        scanf("%d", &new_tasks);

        if (new_tasks == -1) break;

        num_tasks += new_tasks;

        if (num_tasks > cap) {
            cap *= 2;
            tasks = realloc(tasks, cap * sizeof(struct Task));
        }

        for (int i = 0; i < new_tasks; i++) {
            printf("Enter Task ID, Arrival Time, Priority, Burst Time for task %d: ", i + 1);
            scanf("%d %d %d %d", &tasks[num_tasks - new_tasks + i].id,
                  &tasks[num_tasks - new_tasks + i].arrival,
                  &tasks[num_tasks - new_tasks + i].prio,
                  &tasks[num_tasks - new_tasks + i].burst);
            tasks[num_tasks - new_tasks + i].done = 0;
        }

        schedule_task(tasks);
    }

    while (exec_idx < num_tasks) {
        schedule_task(tasks);
    }

    show_exec_order(tasks);
    show_metrics(tasks);

    free(tasks);
    free(exec_order);

    return 0;
}