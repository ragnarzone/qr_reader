#include <stdio.h>
#include <stdlib.h>

int main(){

    fd = open("/dev/ttyUSB0", O_RDWR);
    close(fd)

    FILE *fptr;

    fptr = fopen("/dev/ttyUSB0", "w");

    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }

    fprintf(fptr, "Hello");
    fscanf(fptr,)
    fclose(fptr);
    
    return 0;
}