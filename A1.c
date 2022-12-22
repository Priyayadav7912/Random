#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
    // srand(time(NULL));
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
    if (mkfifo("fifo_recieve_file", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("colud not create fifo file\n");
            return 1;
        }
    }
    if (mkfifo("fifo_send_file", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("colud not create fifo file\n");
            return 1;
        }
    }
    int rf = open("fifo_recieve_file", O_RDONLY);
    if (rf == -1)
    {
        perror("error opening fifo_recieve_file");
        return -1;
    }
    int sf = open("fifo_send_file", O_WRONLY);
    if (sf == -1)
    {
        perror("error opening fifo_send_file");
        return -1;
    }
 
    int l=0;
    for(int i=0;i<50;i+=5){
        for (int j = i; j < i + 5; i++)
        {
            if (write(sf, &arr[j], sizeof(arr[j])) == -1)
            {
                perror("write failed");
                return -1;
            }
            printf("string send is  %s\n", arr[j].str);
        }

        read(rf, &l, sizeof(int));
        printf(" highest id recieved back is %d\n", l);
      
    }
    close(sf);
    printf("fifo_send_file closed\n");
    close(rf);
    printf("fifo_recieve_file closed\n");
}
