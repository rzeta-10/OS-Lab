//CS22B1093 ROHAN G

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>

#define MAX 100

int arr[MAX];

int main(){
    int n;
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    
    pid_t id;
    id=fork();
    
    if(id<0){
        printf("Error in Fork\n");
        exit(0);
    }
    else if(id>0){
        int min=arr[0];
        for(int i=0;i<n;i++){
            arr[i]=arr[i]-3;
            if(min>arr[i]){
                min=arr[i];
            }
        }
        printf("The minimum element is = %d\n",min);
        printf("The elements are \n");
        for(int i=0;i<n;i++){
            printf("%d ,address = %p\n",arr[i],(void*)&arr[i]);
        }
        printf("Parent process , pid = %d ; parent pid = %d\n",getpid(),getppid());
    }
    else{
        printf("---------------------------\n");
        int max=arr[0];
        for(int i=0;i<n;i++){
            arr[i]=arr[i]+2;
            if(max<arr[i]){
                max=arr[i];
            }
        }
        printf("The maximum element is = %d\n",max);
        printf("The elements are \n");
        for(int i=0;i<n;i++){
            printf("%d ,address. = %p\n",arr[i],(void*)&arr[i]);
        }
        printf("Child process , pid = %d ; parent pid = %d\n",getpid(),getppid());
    }
}