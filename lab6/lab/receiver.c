//CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

// Function to count vowels
int count_vowels(const char *message) {
    int count = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        char c = tolower(message[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;

    // Create or get the message queue
    msgid = msgget((key_t)1093, 0666 | IPC_CREAT);

    // Receive message from Sender1 (message type 1)
    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);
    printf("Receiver: Message from Sender1: %s\n", message.mtext);
    printf("Length: %ld\n", strlen(message.mtext));
    printf("Vowels: %d\n", count_vowels(message.mtext));

    // Receive message from Sender2 (message type 2)
    msgrcv(msgid, &message, sizeof(message.mtext), 2, 0);
    printf("Receiver: Message from Sender2: %s\n", message.mtext);
    printf("Length: %ld\n", strlen(message.mtext));
    printf("Vowels: %d\n", count_vowels(message.mtext));
    
    // Receiver will wait (block) until a message of type 1 is available
    // If no message of type 2 is available, it will not block and return immediately
    // Receiver will accept the first available message, regardless of its type
    // MSG_EXCEPT flag is used to avoid reading a message of type 1

    msgctl(msgid, IPC_RMID, NULL); // Destroys the message queue

    return 0;
}