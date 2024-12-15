// CS22B1093 ROHAN G

#include <stdio.h>
#include <stdbool.h>

#define PROS 6
#define RES 4

int alloc[PROS][RES];
int max[PROS][RES];
int avail[RES];
int need[PROS][RES];

void calneed() {
    for (int i = 0; i < PROS; i++) {
        for (int j = 0; j < RES; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe() {
    int work[RES];
    bool finish[PROS] = {false};
    int safeSeq[PROS];
    int count = 0;

    for (int i = 0; i < RES; i++) {
        work[i] = avail[i];
    }

    while (count < PROS) {
        bool found = false;
        for (int p = 0; p < PROS; p++) {
            if (!finish[p]) {
                bool canAlloc = true;
                for (int j = 0; j < RES; j++) {
                    if (need[p][j] > work[j]) {
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc) {
                    for (int k = 0; k < RES; k++) {
                        work[k] += alloc[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; 
        }
    }

    printf("Safe: ");
    for (int i = 0; i < PROS; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

void req(int process, int request[]) {

    for (int i = 0; i < RES; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < RES; i++) {
        if (request[i] > avail[i]) {
            printf("Unsafe: RES not avail.\n");
            return;
        }
    }

    for (int i = 0; i < RES; i++) {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request granted.\n");
    } else {
        printf("Unsafe: Rolling back request.\n");
        for (int i = 0; i < RES; i++) {
            avail[i] += request[i];
            alloc[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    printf("Enter the alloc matrix:\n");
    for (int i = 0; i < PROS; i++) {
        for (int j = 0; j < RES; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < PROS; i++) {
        for (int j = 0; j < RES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the avail matrix:\n");
    for (int i = 0; i < RES; i++) {
        scanf("%d", &avail[i]);
    }

    calneed();

    if (!isSafe()) {
        printf("The initial state is not safe.\n");
        return 0;
    }

    while (1) {
        int process;
        int request[RES];

        printf("\nEnter process number (0-5) or -1 to exit: ");
        scanf("%d", &process);
        if (process == -1) break;

        printf("Enter the request for process P%d:\n", process);
        for (int i = 0; i < RES; i++) {
            scanf("%d", &request[i]);
        }

        req(process, request);
    }

    return 0;
}