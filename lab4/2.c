//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAX 100

int main()
{
    int status;
    pid_t p1,p2;
    p1 = fork();
    
    if(p1<0){
        printf("\nError");
        exit(0);
    }
    if(p1>0){
        wait(&status);
        printf("\n-------------------------------------------\n");
        int n;
        printf("Enter the size of the array : ");
        scanf("%d",&n);
        
        printf("\nEnter the elements in the array : ");
        int *arr = (int*)malloc(n*sizeof(int));
        
        for(int i = 0; i<n; i++){
            scanf("%d",&arr[i]);
        }
        printf("\nThe elements in the array are : ");
        for(int i = 0; i<n; i++){
            printf("\n%d elements is -%d with address %p",i+1,arr[i],(void*)&arr[i]);
        }
        int swapped;
        int temp;
        for (int i = 0; i < n - 1; i++) {
            swapped = 0;
        
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = 1;
                }
            }
        
        
            if (swapped == 0)
                break;
        }
        printf("\nAfter the sorting the array , the elements in the array are : ");
        for(int i = 0; i<n; i++){
            printf("\n%d elements is -%d with address %p",i+1,arr[i],(void*)&arr[i]);
        }
        free(arr);
        printf("\n-------------------------------------------\n");
    }else{
        printf("\n-------------------------------------------\n");
        
        int n;
        printf("Enter the size of the array : ");
        scanf("%d",&n);
        
        printf("\nEnter the elements in the array : ");
        int *arr = (int*)malloc(n*sizeof(int));
        
        for(int i = 0; i<n; i++){
            scanf("%d",&arr[i]);
        }
        printf("\nThe elements in the array are : ");
        for(int i = 0; i<n; i++){
            printf("\n%d elements is -%d with address %p",i+1,arr[i],(void*)&arr[i]);
        }
        
        int mid = n/2;
        for(int i = 0; i<mid; i++){
            arr[i]=arr[n-i-1]^arr[i];
            arr[n-i-1]=arr[i]^arr[n-i-1];
            arr[i]=arr[i]^arr[n-i-1];
        }
        
        printf("\nThe array in reverse order is : ");
        for(int i = 0; i<n; i++){
            printf("\n%d elements is -%d with address %p",i+1,arr[i],(void*)&arr[i]);
        }
        free(arr);
        printf("\n-------------------------------------------\n");
    }
    return 0;
}