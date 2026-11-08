//Include of the needed libraries and the different header files
#include<stdio.h>
#include<stdlib.h>
#include"MLFQ.h"
#include"data.h"
#include"Round_Robin.h"
#define numberTask 20
#define quantum 20 //The Time Slice

int main(int argc(),char argv[]){

//Different Workloads
int
shortTask[]={3, 5, 2, 4, 6, 3, 5, 7, 4, 2, 6, 3, 5, 4, 2, 7, 6, 3, 5, 4},
mixtureTask[]={4, 15, 8, 22, 3, 12, 27, 6, 19, 5, 30, 9, 14, 2, 25, 11, 7, 20, 13, 6},
longTask[]={25, 30, 42, 18, 35, 22, 40, 28, 33, 45, 20, 38, 26, 31, 48, 24, 36, 29, 41, 34};

//Execution of the Different CPU Scheduling
MultiLevel_Feedback_Queue(shortTask,numberTask,quantum);
MultiLevel_Feedback_Queue(mixtureTask,numberTask,quantum);
MultiLevel_Feedback_Queue(longTask,numberTask,quantum);

Round_Robin(shortTask,numberTask,quantum);
Round_Robin(mixtureTask,numberTask,quantum);
Round_Robin(longTask,numberTask,quantum);

return 0;
}

