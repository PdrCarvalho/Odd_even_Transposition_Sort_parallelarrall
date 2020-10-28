#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

MPI_Status status;

int main(int argc, char *argv[])
{
    time_t start_process = time(NULL);
    int N = atoi(argv[1]);
    int cores = atoi(argv[2]);
    int local_N = N / cores;
    int local_2N = local_N * 2;
    srand(10);
    int temp;
    int array[N];
    int local_array[local_N];
    int remote_array[local_N];
    int local_array2N[local_2N];
    for (int i = 0; i < N; i++)
    {
        array[i] = rand()%1000;
        //printf("%d - %d \n",i,array[i]);
    }
    int numtasks, taskid;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Scatter(array, local_N, MPI_INT, &local_array, local_N, MPI_INT, 0, MPI_COMM_WORLD);
    for (int phase = 0; phase < local_N; phase++)
    {
        if (phase % 2 == 0)
        {
            for (int i = 1; i < local_N; i += 2)
            {
                if (local_array[i - 1] > local_array[i])
                {
                    temp = local_array[i];
                    local_array[i] = local_array[i - 1];
                    local_array[i - 1] = temp;
                }
            }
        }
        else
        {
            for (int i = 1; i < local_N - 1; i += 2)
            {
                if (local_array[i] > local_array[i + 1])
                {
                    temp = local_array[i];
                    local_array[i] = local_array[i + 1];
                    local_array[i + 1] = temp;
                }
            }
        }
    }
    //printf("Processo %d com [%d,%d,%d,%d]\n",taskid,local_array[0],local_array[1],local_array[2],local_array[3]);
    // Looping de numeros de processos
    for (int core_phase = 0; core_phase < cores; core_phase++)
    {
        if (taskid % 2 != 0)
        {
            if (core_phase % 2 == 0)
            {
                MPI_Send(&local_array, local_N, MPI_INT, taskid - 1, core_phase, MPI_COMM_WORLD);
                MPI_Recv(&local_array, local_N, MPI_INT, taskid - 1, core_phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            else if(taskid!=cores-1)
            {
                MPI_Recv(&remote_array, local_N, MPI_INT, taskid + 1, core_phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int i = 0; i < local_N; i++)
                {
                    local_array2N[i] = local_array[i];
                }
                for (int i = 0; i < local_N; i++)
                {
                    local_array2N[local_N + i] = remote_array[i];
                }

                for (int phase = 0; phase < local_2N; phase++)
                {
                    if (phase % 2 == 0)
                    {
                        for (int i = 1; i < local_2N; i += 2)
                        {
                            if (local_array2N[i - 1] > local_array2N[i])
                            {
                                temp = local_array2N[i];
                                local_array2N[i] = local_array2N[i - 1];
                                local_array2N[i - 1] = temp;
                            }
                        }
                    }
                    else
                    {
                        for (int i = 1; i < local_2N - 1; i += 2)
                        {
                            if (local_array2N[i] > local_array2N[i + 1])
                            {
                                temp = local_array2N[i];
                                local_array2N[i] = local_array2N[i + 1];
                                local_array2N[i + 1] = temp;
                            }
                        }
                    }
                }
                for (int i = 0; i < local_N; i++)
                {
                    local_array[i] = local_array2N[i];
                }
                for (int i = 0; i < local_N; i++)
                {
                    remote_array[i] = local_array2N[local_N + i];
                }

                MPI_Send(&remote_array, local_N, MPI_INT, taskid + 1, core_phase, MPI_COMM_WORLD);
            }
            
        }
        else
        {
            if (core_phase % 2 == 0)
            {
                MPI_Recv(&remote_array, local_N, MPI_INT, taskid + 1, core_phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int i = 0; i < local_N; i++)
                {
                    local_array2N[i] = local_array[i];
                }
                for (int i = 0; i < local_N; i++)
                {
                    local_array2N[local_N + i] = remote_array[i];
                }

                for (int phase = 0; phase < local_2N; phase++)
                {
                    if (phase % 2 == 0)
                    {
                        for (int i = 1; i < local_2N; i += 2)
                        {
                            if (local_array2N[i - 1] > local_array2N[i])
                            {
                                temp = local_array2N[i];
                                local_array2N[i] = local_array2N[i - 1];
                                local_array2N[i - 1] = temp;
                            }
                        }
                    }
                    else
                    {
                        for (int i = 1; i < local_2N - 1; i += 2)
                        {
                            if (local_array2N[i] > local_array2N[i + 1])
                            {
                                temp = local_array2N[i];
                                local_array2N[i] = local_array2N[i + 1];
                                local_array2N[i + 1] = temp;
                            }
                        }
                    }
                }
                for (int i = 0; i < local_N; i++)
                {
                    local_array[i] = local_array2N[i];
                }
                for (int i = 0; i < local_N; i++)
                {
                    remote_array[i] = local_array2N[local_N + i];
                }

                MPI_Send(&remote_array, local_N, MPI_INT, taskid + 1, core_phase, MPI_COMM_WORLD);
            }
            else if(taskid!=0)
            {
                MPI_Send(&local_array, local_N, MPI_INT, taskid - 1, core_phase, MPI_COMM_WORLD);
                MPI_Recv(&local_array, local_N, MPI_INT, taskid - 1, core_phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(local_array, local_N, MPI_INT, array, local_N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    
    /* 
        printf("\n");
        for (int i = 0; i < N; i++)
        {
            printf("%d ", array[i]);
            if (i == N - 1)
                printf("\n");
        }
    }
     else */
    if (taskid != 0)
    {
        return 0;
    }

    time_t end_process = time(NULL);
    FILE *fp;
    char outputFilename[] = "parallel_code.txt";
    fp = fopen(outputFilename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    fprintf(fp, "%d,%ld,%d\n", N,(end_process - start_process),cores);
    fclose(fp); 
    return 0;
}
