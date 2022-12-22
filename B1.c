// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
// #define MAX 10

char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$&*";
    if (size)
    {
        --size;
        for (size_t n = 0; n < size; n++)
        {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}
struct data
{
    char str[128];
    int id;
};

// structure for message queue
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

int main()

{
    srand(time(NULL));
    struct data arr[50];
    int i = 0;
    while (i < 50)
    {
        arr[i].id = i;
        char *strng;
        size_t sz = 6;
        strcpy(arr[i].str, rand_string(strng, sz));
        i++;
    }

    key_t key;
    int msgid;
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    for(int j = 0; j < 50; j+=5)
    {
        for (int i = j; i < j+5; i++)
        {
            message.mesg_type = arr[i].id;

            strcpy(message.mesg_text, arr[i].str);

            msgsnd(msgid, &message, sizeof(message), 0);

            printf("Data send is : %s  %d \n", message.mesg_text, message.mesg_type);
        }
        // char bf[10];
        int l=0;
        msgrcv(msgid, &l, sizeof(l), 0, 0);
        printf("highest index of message recieved is : %d \n",l);
    }

    return 0;
}
