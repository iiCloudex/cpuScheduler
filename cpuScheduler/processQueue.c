#include "processQueue.h"

PROCESS *processTable; // an array of all processes
int processTableSize = 0;

PROCESS **readyQueue; // an array of pointers to the processes in the processTable
int readyQueueSize = 0;

// constructor of the process table
void createProcessTable(int capacity)
{
    processTable = (PROCESS *) malloc(capacity * sizeof(PROCESS));
}

// constructor of the ready queue
void createReadyQueue(int capacity)
{
    readyQueue = (PROCESS **) malloc(capacity * sizeof(PROCESS *));
}

// adds a process and expands the table if necessary
void addProcessToTable(PROCESS process)
{
    if(processTableSize < sizeof(processTable))
    {
        processTable[processTableSize] = process;
        processTableSize++;
    }
    else
    {
        processTable = (PROCESS *) realloc(processTable, 2*sizeof(processTable));
        processTable[processTableSize] = process;
        processTableSize++;
    }
}

void displayProcessTable()
{
    printf("PROCESSES:\nName\tEntry\tBurst\n");

    for(int i = 0; i < processTableSize; i++)
        printf("%s    \t%d\t%d\n", processTable[i].name, processTable[i].entryTime, processTable[i].burstTime);
    

    printf("\n");
}

// finds the shortest job in the ready queue and returns its location in the queue
int findShortestJob()
{
    int shortest = -1;
    int min = 2000;

    for(int i = 0; i < readyQueueSize; i++)
    {
        if(readyQueue[i]->burstTime < min)
        {
            min = readyQueue[i]->burstTime;
            shortest = i;
        }
    }

    return shortest;
}


// adds any processes that arrive at the current time to the readyQueue
PROCESS *arrivingProcess(int time)
{
    for(int i = 0; i < processTableSize; i++)
        if(processTable[i].entryTime == time)
            return &processTable[i];
            
    return NULL;
}

// determines if any processes in the process queue have more to execute
bool processesLeftToExecute()
{
    for(int i = 0; i < processTableSize; i++)
    {
        if(processTable[i].burstTime > 0)
            return true;
    }

    return false; //return 0 if all processes are complete
}


// adds a pointer and expands the ready queue if necessary
void addProcessToReadyQueue(PROCESS *pointer)
{
    if(readyQueueSize < sizeof(readyQueue))
    {
        readyQueue[readyQueueSize] = pointer;
        readyQueueSize++;
    }
    else
    {
        readyQueue = (PROCESS **) realloc(readyQueue, 2*sizeof(readyQueue));
        readyQueue[readyQueueSize] = pointer;
        readyQueueSize++;
    }
}

// exposes a specific process in the ready queue (it stays in the queue)
PROCESS *getProcessFromReadyQueue(int index)
{
    return readyQueue[index];
}

// gets a specific process from the ready queue (it gets removed from the queue)
PROCESS *fetchProcessFromReadyQueue(int index)
{
    PROCESS *proc = readyQueue[index];

    removeProcessFromReadyQueue(index);

    return proc;
}

// removes the process at index from the ready queue and returns a pointer to it
PROCESS *removeProcessFromReadyQueue(int index)
{
    PROCESS *removed = NULL;

    if(index > readyQueueSize - 1)
        printf("Invalid index\n");
    else
    {
        removed = readyQueue[index];
        readyQueue[index] = NULL;

         if (index < readyQueueSize-1)
             memmove(&readyQueue[index], &readyQueue[index+1], ((readyQueueSize-1)-index) * sizeof(readyQueue[0]));

        readyQueue[readyQueueSize-1] = NULL;
        readyQueueSize--;
    }

    return removed;
}

// get size of the ready queue
int getReadyQueueSize()
{
    return readyQueueSize;
}

// displays the contents of the ready queue
void displayQueue()
{
    printf("\nQUEUE:");

    for(int i = 0; i < readyQueueSize; i++)
        printf(" %s(%d)", readyQueue[i]->name, readyQueue[i]->burstTime);

    printf("\n");
}

//calculates the average wait time using information in the proc_queue
//and prints the value.
void printAverageWaitTime()
{
    float avg = 0;

    for(int i = 0; i < processTableSize; i++)
    {
        avg += processTable[i].waitTime;
    }

    avg = avg/processTableSize;

    printf("Average Wait Time: %.2f\n", avg);

}

// clean-up the table and the queue
void cleanUp()
{
    free(processTable);
    free(readyQueue);
}




