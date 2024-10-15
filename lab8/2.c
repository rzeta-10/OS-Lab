//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

int M1[3][3];
int M2[3][3];

int A[3][3];
int S[3][3];
int M[3][3];

void *addition(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            A[i][j] = M1[i][j] + M2[i][j];
        }
    }
}

void *substraction(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            S[i][j] = M1[i][j] - M2[i][j];
        }
    }
}

void *multiplication(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            M[i][j] = 0;
            for(int k = 0; k<3; k++){
                M[i][j] += M1[i][k]*M2[k][j];
            }
        }
    }
}


int main(int argc, char* argv[])
{
    pthread_t th[3];

    printf("\nEnter the values of first matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            scanf("%d",&M1[i][j]);
        }
        //printf("\n");
    }
    printf("\nEnter the values of second matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            scanf("%d",&M2[i][j]);
        }
        //printf("\n");
    }
    
    if(pthread_create(&th[0],NULL,addition,NULL)!=0){
        perror("Error in creating thread");
        exit(0);
    }
    if(pthread_create(&th[1],NULL,substraction,NULL)!=0){
        perror("Error in creating thread");
        exit(0);
    }
    if(pthread_create(&th[2],NULL,multiplication,NULL)!=0){
        perror("Error in creating thread");
        exit(0);
    }
    
    if(pthread_join(th[0],NULL)!=0){
        perror("Error in joining\n");
        exit(0);
    }
    if(pthread_join(th[1],NULL)!=0){
        perror("Error in joining\n");
        exit(0);
    }
    if(pthread_join(th[2],NULL)!=0){
        perror("Error in joining\n");
        exit(0);
    }
    
    printf("\n M1 matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("%d ",M1[i][j]);
        }
        printf("\n");
    }
    
    printf("\n M2 matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("%d ",M2[i][j]);
        }
        printf("\n");
    }
    
    printf("\n A matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    
    printf("\n S matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("%d ",S[i][j]);
        }
        printf("\n");
    }
    
    printf("\n M matrix : \n");
    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}