#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <sys/time.h>

int main(int argc, char const *argv[])
{
    time_t start_process = time(NULL);
    int N = atoi(argv[1]);
    srand(10);
    int temp;
    int array[N];
    for (int i = 0; i < N; i++)
    {
        array[i] = rand()%100;
    }
    for (int phase = 0; phase < N; phase++)
    {
        if (phase%2==0){
            for (int i = 1; i < N; i+=2)
            {
                if (array[i-1]> array[i]){
                    temp = array[i];
                    array[i] = array[i-1];
                    array[i-1]= temp;
                }
            }
            
        }
        else
        {
            for (int i = 1; i < N-1; i+=2)
            {
                if (array[i]>array[i+1]){
                    temp = array[i];
                    array[i] = array[i+1];
                    array[i+1]= temp;
                }
            }
            
        }
        
    }
    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "serial_time.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp,"%d,%ld,\n", N,(end_process - start_process));
    fclose(fp);
    return 0;
}
