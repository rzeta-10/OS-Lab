// CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 100

int main() {
    int shmid;
    key_t key;
    int *shm, *s;
    key = 1093;  // Unique key for shared memory

    pid_t p1;
    p1 = fork();  // Create child process

    if (p1 < 0) {  // Error in fork
        printf("\nError in creating the child process");
        exit(1);
    } else if (p1 > 0) {  // Parent process
        // Create shared memory segment
        printf("\n-----------------------\n");
        printf("Parent Process : ");
        if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }
        printf("Shared memory id %d\n", shmid);

        //Attach shared memory to parent process
        if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
            perror("shmat");
            exit(1);
        }
        printf("SHM address in parent process is %p\n", shm);

        // Read from shared memory
        s = shm;
        int count = 10;
        sleep(20);  // Wait for child process to write
        printf("\nParent Process reading : ");
        for (int i = 0; i < count; i++) {
            printf("%d ", *s);
            s++;
        }

        // Modify and display updated shared memory
        s = shm;
        printf("\nParent Process modifying : ----");
        printf("\nParent Process displaying : ");
        for (int i = 0; i < count; i++) {
            *s += 2;
            printf("%d ", *s);
            s++;
        }

        // Detach shared memory
        int k = shmdt(shm);
        if (k == -1) {  
            perror("shmdt");
        }

        // Mark the shared memory segment for deletion
        int v = shmctl(shmid, IPC_RMID, NULL);
        if (v == -1) {
            perror("shmctl");
        } else {
            printf("\nShared memory cleared successfully.\n");
        }
        
        printf("\n-----------------------\n");

        return 0;

    } else {  // Child process
        sleep(5);  // Allow parent process to set up shared memory
        printf("\n-----------------------\n");
        printf("Child process : ");
        // Access the shared memory created by the parent
        if ((shmid = shmget(key, SHMSIZE, 0666)) < 0) {
            perror("shmget");
            exit(1);
        }

        // Attach shared memory to child process
        if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
            perror("shmat");
            exit(1);
        }
        printf("SHM address in child process %p\n", shm);
        printf("SHM memory id in child process: %d\n", shmid);

        // Write 10 integers to the shared memory
        int count = 0;
        printf("\nChild Process writing, enter 10 integer values: ");
        for (s = shm; count < 10; count++) {
            scanf("%d", s++);
        }
        printf("\nCompleted taking input in the child process\n");

        // Detach shared memory
        int k = shmdt(shm);
        if (k == -1) {
            perror("shmdt");
        }
        // int v = shmctl(shmid, IPC_RMID, NULL);
        // if (v == -1) {
        //     perror("shmctl");
        // } else {
        //     printf("\nShared memory cleared successfully.\n");
        // }
        
        printf("\n-----------------------\n");

    }
    return 0;
}

//using sleep since the shared memory is being created in parent process , so child has to wait until the its created
//on running the code multiple times , shmctl is giving error as that instance is not getting cleared from the memory 
//using shmctl in child process makes the parent read garbage values 
//if key is different , the code throws the error no such file or directory

//when shmid is commented out , shmat throws an error of invalid argument and child process throws an error
//when shmat is commneted out , the code gives segmentation fault
//when shmdt is commneted out , the code does not throw any error memory leaks might occur as both process is attached to the shm
//when shmctl is commented out , the code may not throw an error , but may lead to bottlenecks later as the shared memory is not erased
