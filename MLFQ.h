#include<stdlib.h>
#pragma once
#include"data.h"
#include"Round_Robin.h"
#define boostThresold 1000
#define numberQueues 3

//Function to place a new process into the queue
void enqueue(queue *queue,int burstTime,int id){
    element *newElement=malloc(sizeof(element));
    if(queue==NULL || newElement==NULL)
        exit(EXIT_FAILURE);
    //set the caracterics of the process
    newElement->burstTime=burstTime;
    newElement->id=id;
    newElement->next=NULL;
    newElement->waitedTime=0;

    if(queue->first!=NULL){//Check if the queue contains a process
        element *currentElement=queue->first;
        //move to untill tail of the queue
        while(currentElement->next!=NULL){
                currentElement=currentElement->next;//Move between element until the last element
            }
            currentElement->next=newElement;//Place the object after the last element
    }else//That element is the first process in the queue
                queue->first=newElement;
    }
//Function to remove the First element from the queue
element* dequeue(queue *queue){
    if(queue==NULL || queue->first==NULL)
        exit(EXIT_FAILURE);

        element *temp=queue->first;//Head of the queue
        queue->first=temp->next;//The next element in the queue
        temp->next=NULL;

    return temp;//Return the new queue of length-1
}
//Function to calculate the length of the queue
int length(queue *queue){
    int length=0;
    element *currentElement=queue->first;
    while(currentElement!=NULL){
        length++;
        currentElement=currentElement->next;

    }
    return length;
}
//Function to check if the quee is empty or not
bool empty(queue *queue){

return (queue->first==NULL || queue==NULL);
}

//Implementation of the MLFQ(RR(Q)+RR(2Q)+RR(3Q)) without arrival time
void MultiLevel_Feedback_Queue(int *burstTime, int size, int quantum){
    int length=0,completionTime=0,contextSwitches=0,averageTurnAroundTime=0,averageRespondTime=0,averageWaitingTime=0,maximunRespondTime=0;
    float throughPut=0,timeSwitch=0,utilization=0;
    int *turnAroundTime=malloc(sizeof(int)*size),*waitingTime=malloc(sizeof(int)*size),*responseTime=malloc(sizeof(int)*size),*temp=malloc(sizeof(int)*size),*first=malloc(size*sizeof(int)),*executed=malloc(sizeof(int)*size);
    queue *queues[numberQueues];


    //Initialization of all the array
    for(int i=0;i<size;i++){
        temp[i]=burstTime[i];//Save the initial burst time of each process
        turnAroundTime[i]=0;
        waitingTime[i]=0;
        responseTime[i]=0;
        first[i]=0;
        executed[i]=0;
    }

    // Dynamically allocate each queue
    for(int i = 0; i < numberQueues; i++) {
        queues[i] = malloc(sizeof(queue));
        queues[i]->first = NULL;
    }

    // Enqueue all processes into the Highest Priority Queue (Queue 0)
    for(int i = 0; i < size; i++){
        enqueue(queues[0], burstTime[i], i);
    }

    // MLFQ Loop
    do {
        int timePass=0;
        // Aging of the process
        for(int i=1;i<numberQueues;i++){//Start From the next queue
            element *currentElement=queues[i]->first;//Head of the other queue
            element *previousElement=NULL;
            while(currentElement!=NULL){//DO nothing if the queue is empty
                if(currentElement->waitedTime>=boostThresold){//Process already wait too long
                    //Save the previous element
                    if(previousElement==NULL)
                        queues[i]->first=currentElement->next;
                    else
                        previousElement->next=currentElement->next;
                //Promotion of that process
                element *nextElement=currentElement->next;
                currentElement->next=NULL;
                int burst=currentElement->burstTime,id=currentElement->id;
                free(currentElement);
                enqueue(queues[i-1],burst,id);//Process Promotion to the Highest Queue
                contextSwitches++;//Count the switch between process
                currentElement=nextElement;
                }else{//The process haven't take long in the queue
                    //Continue and check for the next process
                    previousElement=currentElement;
                    currentElement=currentElement->next;
                }
            }
        }
        // Round Robin execution across the queues with the quantum of i*q
        int activeQueue = -1;
        for(int i = 0; i < numberQueues; i++) {
            if(!empty(queues[i])) {//Update the current queue quantum
                activeQueue = i;
                break;
            }
        }
        //Check if the current queue is not empty,if yes skip it
        if(activeQueue == -1) break;

        // Dequeue the process from the highest available priority queue
        element *currentElement = dequeue(queues[activeQueue]);
        if(currentElement == NULL) continue;

        int processId = currentElement->id;

        // Track first response time
        if(executed[processId] == 0) {
            responseTime[processId] = completionTime;//First Executed Time
            executed[processId] = 1;//Mark executed
        }
        int burst = quantum * (activeQueue + 1);// Calculate quantum for the current queue Q, 2Q, 3Q
        //Treat the current process for a time quantum
        if(currentElement->burstTime > burst){
            currentElement->burstTime -= burst;
            completionTime += burst;
            timePass = burst;//Save the CPU Burst Time Passed

            // Depromotion the pass thread to the lower queue
            if(activeQueue + 1 < numberQueues){
                enqueue(queues[activeQueue + 1], currentElement->burstTime, processId);
            } else {
                enqueue(queues[activeQueue], currentElement->burstTime, processId);
            }
            free(currentElement);
        } else {
            //Treat the current process for his left time quantum
            int runTime = currentElement->burstTime;
            completionTime += runTime;
            currentElement->burstTime = 0;
            timePass = runTime; //Save the CPU Burst Time Passed

            //Calculate the performance metrics
            turnAroundTime[processId] = completionTime;
            waitingTime[processId] = turnAroundTime[processId] - temp[processId];
            free(currentElement);
            length++;//Move to the next queue
        }
        contextSwitches++;
        //Update the process age standing in the other queue
        for(int j = 0; j < numberQueues; j++){
            element *node = queues[j]->first;
            while(node != NULL){
                if(node->id != processId)
                    node->waitedTime += timePass;
                node = node->next;
            }
        }
    } while(length < size);

        //Compute the other metrics
        maximunRespondTime = maximun(responseTime, size);
        timeSwitch = (float)contextSwitches / size;
        throughPut = (float)size / completionTime;
        utilization=(float)(average(temp,size)*size)/completionTime*100;
        //Display the parameters to the terminal
        printf("\n===================MultiLevel Feedback Queue===================\n");
        printf("The Average Turn Around Time: %0.2f\n", average(turnAroundTime, size));
        printf("The Average Waiting Time: %0.2f\n", average(waitingTime, size));
        printf("The Average Response Time: %0.2f\n", average(responseTime, size));
        printf("The Maximun Respond Time: %d\n", responseTime[maximunRespondTime]);
        printf("The Time Switches: %0.2f\n", timeSwitch);
        printf("The Throughput: %0.3f\n", throughPut);
        printf("The Context Switches: %d\n", contextSwitches);
        printf("The CPU Utilization: %0.2f\n",utilization);

        //Save all the parameters into a separate file to be use and anlyse later
        save_txt("results_MLFQ.csv", "a", average(turnAroundTime, size), average(waitingTime, size), average(responseTime, size), timeSwitch, utilization, contextSwitches);
        //clean th Heap
        free(temp);
        free(turnAroundTime);
        free(waitingTime);
        free(responseTime);
        free(first);
        free(executed);
        //Delete the queues
        for(int i = 0; i < numberQueues; i++) {
            free(queues[i]);
        }
}










