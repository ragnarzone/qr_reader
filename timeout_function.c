#include <stdio.h>
#include <time.h>

int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}

    return  1;
}

int main ()
{
    char name[20];
    printf("Enter Username: (in 15 seconds)\n");
    printf("Time start now!!!\n");

    scanf("%s",name);
    if( timeout(5) == 1 ){
        printf("Time Out\n");
        return 0;
    }

    printf("Thnaks\n");
    return 0;
}

