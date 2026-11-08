#pragma once

//Function the maximun of an array
int maximun(int *array,int size){
    int index=0,max=array[index];
    for(int i=1;i<size;i++){
        if(max<array[i])
            index=i;
        max=array[index];
    }
    return index;
}
//Calculate the average of an array
float average(int *array,int size){
    int sum=0,average;
    for(int i=0;i<size;i++){
        sum=sum+array[i];
    }
    return (float)sum/size;
}

//Round Robin Implementation
void Round_Robin(int *burstTime,int size,int quantum){
    int length=0,completionTime=0,contextSwitches=0,averageTurnAroundTime=0,averageRespondTime=0,averageWaitingTime=0,maximunRespondTime=0;
    float throughPut=0,timeSwitch=0,utilization=0;
    int *turnAroundTime=malloc(sizeof(int)*size),*waitingTime=malloc(sizeof(int)*size),*responseTime=malloc(sizeof(int)*size),*temp=malloc(sizeof(int)*size),*first=malloc(size*sizeof(int)),*executed=malloc(sizeof(int)*size);

//Initialization of all the array
for(int i=0;i<size;i++){
    temp[i]=burstTime[i];//Save the initial burst time of each process
    turnAroundTime[i]=0;
    waitingTime[i]=0;
    responseTime[i]=0;
    first[i]=0;
    executed[i]=0;
}

while(size>length){//Loop until all the Process are being treat by the CPU
    for(int i=0,count=0;i<size;i++){//Process the Process in the queue
        if(burstTime[i]==0){//Process the incomplete threads
            continue;
        }

        if(burstTime[i]>0 && !executed[i]){//Save the first execution time for all the process
            first[i]=completionTime;
        }
        //Treat the current process for a time quantum
        if(burstTime[i]>quantum){
            //Execute it
            burstTime[i]=burstTime[i]-quantum;
            completionTime=completionTime+quantum;
        }else{
            //Termibated the rest of the task for the process i
            completionTime=completionTime+burstTime[i];
            burstTime[i]=0;
            //Compute the different measurments for each process
            turnAroundTime[i]=completionTime;
            waitingTime[i]=turnAroundTime[i]-temp[i];
            responseTime[i]=first[i];
            length++;//Remove the current completed process
        }
        contextSwitches++;//Count the Pre-empted Process
        executed[i]++;//Move to the next process
    }
}

//Compute the other metrics
maximunRespondTime=maximun(responseTime,size);
timeSwitch=(float)contextSwitches/size;
throughPut=(float)size/completionTime;
utilization=(float)(average(temp,size)*size)/completionTime*100;

//Display all the results
printf("\n===================Round Robin===================\nData Executed,Saved and Ploted\nSummary:\n");
printf("The Average Turn Around Time:%0.2f\n",average(turnAroundTime,size));
printf("The Average Waiting Time:%0.2f\n",average(waitingTime,size));
printf("The Average Response Time:%0.2f\n",average(responseTime,size));
printf("The Maximun Respond Time:%d\n",responseTime[maximunRespondTime]);
printf("The Time Switches:%0.2f\n",timeSwitch);
printf("The throughPut:%0.3f\n",throughPut);
printf("The Context Switches:%d\n",contextSwitches);
printf("The CPU Utilization: %0.2f\n", utilization);

//Save all the parameters into a separate file to be use and anlyse later
save_txt("results_RR.csv","a",average(turnAroundTime,size),average(waitingTime,size),average(responseTime,size), timeSwitch,utilization,contextSwitches);
//Delete the queues
free(temp);
free(turnAroundTime);
free(waitingTime);
free(responseTime);
free(first);
free(executed);

}

