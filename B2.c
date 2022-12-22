// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
// structure for message queue
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv to receive message
    for(int j=0;j<50;j+=5)
    {
        int mx=0;
        for (int i = 0; i < 5; i++)
        {
            msgrcv(msgid, &message, sizeof(message), 0, 0);

            // display the message
            printf("string  Received with id is  : %s  %d \n",
                   message.mesg_text, message.mesg_type);
            if(message.mesg_type>mx){
                mx=message.mesg_type
            }
        }
        // char bf[10];
        // sprintf(bf, "%d", mx)
        msgsnd(msgid, &mx, sizeof(mx), 0);

        
    }
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
