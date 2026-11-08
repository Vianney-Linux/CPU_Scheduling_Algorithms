#pragma once//New   Version of #IFNDEF,include the header only once
#define numberTask 20

//An single process
typedef struct element element;
    struct element{
        //Caracteritics of a process
        int burstTime;
        int id;
        bool executed;
        int waitedTime;
        element *next;
    };

//The queue of process
typedef struct queue queue;
    struct queue{
        element *first;
    };


//Functin to sav the parameter into separate files to be analyse later
FILE *save_txt(char* name,const char* mode,float averageTurnAroundTime,float averageWaitingTime,float averageResponseTime,float timeSwitch,float throughput,int contextSwitches){
    FILE *results=fopen(name,mode);
    fprintf(results,"%0.2f %0.2f% 0.2f %0.2f %d %0.2f\n",averageTurnAroundTime , averageWaitingTime , averageResponseTime, throughput , contextSwitches ,timeSwitch);
    fprintf(results,"\n\n");
    fclose(results);
return results;
}

