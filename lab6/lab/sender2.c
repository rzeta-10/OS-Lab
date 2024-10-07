//CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;
    char buffer[100];

    // Create a message queue
    msgid = msgget((key_t)1093, 0666 | IPC_CREAT);

    message.mtype = 2; // Different message type
    printf("Sender2: Enter a message: ");
    scanf("%s", buffer);
    strcpy(message.mtext, buffer);

    // Send the message to the queue
    if(msgsnd(msgid, &message, sizeof(message.mtext), 0)==-1){ // 0 flag implies blocking mode
        perror("msgsnd");
        exit(1);
    }
    
    printf("Sender2: Message sent!\n");
    return 0;
}