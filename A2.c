#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

struct data
{
    char str[128];
    int id;
};

int main(int argc, char *argv[])
{
    struct data arr[5];
    int sf = open("fifo_send_file", O_RDONLY);
    if (sf == -1)
    {
        printf("colud not create fifo file\n");
        return 1;
    }
    int rf = open("fifo_recieve_file", O_WRONLY);
    if (rf == -1)
    {
        perror("error opening fifo_recieve_file");
        return -1;
    }
    
    for(int j=0;j<50;j+=5)
    {
       
        int mx = 0; // varible to store maximum id 
        for (int i = 0; i < 5; i++)
        {
            if (read(sf, &arr[i], sizeof(arr[i])) == -1)
            {
                perror("error reading fifo_recieve_file");
                return -1;
            }
            printf("string received is %s\n", arr[i].str);
            if(arr[i].id>mx){
                mx=arr[i].id;
            }
        }
        
        if (write(rf, &mx, sizeof(int) )== -1)
        {
            perror("error writing fifo_recieve_file");
            return -1;
        }
        
    }

    close(sf);
    printf("fifo_send_file closed\n");
    close(rf);
    printf("fifo_recieve_file closed\n");
}
