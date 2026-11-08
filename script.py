import pandas
import matplotlib.pyplot
import numpy


def graphEach():
    metrics=['Average Turn Around Time' , 'Average Waiting Time' , 'Average Response Time', 'CPU Utilization' , 'Context Switches' ,'Time Switch']
    #For the Round-Robin Algorithm
    RR=pandas.read_csv("results_RR.csv", sep=r"\s+",header=None)#Read and Extract data
    RR.columns=metrics
    #For the MultiLevel Feedback Queue
    MLFQ=pandas.read_csv("results_MLFQ.csv", sep=r"\s+",header=None)#Read and Extract data
    MLFQ.columns=metrics

    #Plot the result data for each type of Workloads
    typeTasks={"Short":0,"Mixture":1,"Long":2}
    for typeTask,i in typeTasks.items():
        data={"RoundRobin":RR.iloc[i].to_dict(),"MLFQ":MLFQ.iloc[i].to_dict()}


        dataFrame=pandas.DataFrame(data).loc[metrics]

        firstGraph=['Average Turn Around Time' , 'Average Waiting Time' , 'Average Response Time']
        secondGraph=[ 'CPU Utilization' , 'Context Switches' ,'Time Switch']


        fig,(ax1,ax2)=matplotlib.pyplot.subplots(figsize=(15,15),nrows=2,ncols=1)#Graph contains two subgraphs
        #First plot contains three metrics of each CPU Scheduling Algorithms
        dataFrame.loc[firstGraph].plot(ax=ax1,kind='bar',fontsize=20,width=0.25,edgecolor='black',color=['blue','red'])
        #Stylitization of the different plots
        ax1.set_ylabel('Time(ms)',fontsize=14)
        ax1.set_xlabel('Metrics',fontsize=14)
        ax1.set_title(f'Round Robin and MultiLevel Feedback Queue for {typeTask} Workloads',fontsize=20)
        ax1.set_xticks(range(len(firstGraph)))
        ax1.set_xticklabels(firstGraph, rotation=0)
        ax1.legend(title="Algorithms", fontsize=12)
        ax1.grid(axis='y', linestyle='--', alpha=0.5)

        #Second plot contains other three metrics of each CPU Scheduling Algorithms
        dataFrame.loc[secondGraph].plot(kind='bar',ax=ax2,width=0.25,fontsize=20,edgecolor='black',color=['blue','red'])
        #Stylitization of the different plots
        ax2.set_ylabel('Time(ms)',fontsize=14)
        ax2.set_xlabel('Metrics',fontsize=14)
        ax2.set_title(f'Round Robin and MultiLevel Feedback Queue for {typeTask} Workloads',fontsize=20)
        ax2.set_xticks(range(len(secondGraph)))
        ax2.set_xticklabels(secondGraph, rotation=0)
        ax2.legend(title="Algorithms", fontsize=12)
        ax2.grid(axis='y', linestyle='--', alpha=0.5)

        matplotlib.pyplot.tight_layout()#Arrage everything on the same graph
        matplotlib.pyplot.savefig(f"graph{typeTask}.png")#Save the graph as image

#Function to plot only the Average of the result data for each case study
def graphAverage():
    metrics=['Average Turn Around Time' , 'Average Waiting Time' , 'Average Response Time', 'CPU Utilization' , 'Context Switches' ,'Time Switch']
    #For the Round-Robin Algorithm
    RR=pandas.read_csv("results_RR.csv", sep=r"\s+",header=None)
    RR.columns=metrics
    #For the MLFQ Algorithm

    MLFQ=pandas.read_csv("results_MLFQ.csv", sep=r"\s+",header=None)
    MLFQ.columns=metrics



    data={"RoundRobin":RR.mean().to_dict(),"MLFQ":MLFQ.mean().to_dict()}


    dataFrame=pandas.DataFrame(data).loc[metrics]

    firstGraph=['Average Turn Around Time' , 'Average Waiting Time' , 'Average Response Time']
    secondGraph=[ 'CPU Utilization' , 'Context Switches' ,'Time Switch']


    fig,(ax1,ax2)=matplotlib.pyplot.subplots(figsize=(15,15),nrows=2,ncols=1)
    dataFrame.loc[firstGraph].plot(ax=ax1,kind='bar',fontsize=20,width=0.25,edgecolor='black',color=['blue','red'])

    ax1.set_ylabel('Time(ms)',fontsize=14)
    ax1.set_xlabel('Metrics',fontsize=14)
    ax1.set_title('Round Robin and MultiLevel Feedback Queue for Average Results',fontsize=20)
    ax1.set_xticks(range(len(firstGraph)))
    ax1.set_xticklabels(firstGraph, rotation=0)
    ax1.legend(title="Algorithms", fontsize=12)
    ax1.grid(axis='y', linestyle='--', alpha=0.5)

    dataFrame.loc[secondGraph].plot(kind='bar',ax=ax2,width=0.25,fontsize=20,edgecolor='black',color=['blue','red'])
    ax2.set_ylabel('Time(ms)',fontsize=14)
    ax2.set_xlabel('Metrics',fontsize=14)
    ax2.set_title(f'Round Robin and MultiLevel Feedback Queue for Average Results',fontsize=20)
    ax2.set_xticks(range(len(secondGraph)))
    ax2.set_xticklabels(secondGraph, rotation=0)
    ax2.legend(title="Algorithms", fontsize=12)
    ax2.grid(axis='y', linestyle='--', alpha=0.5)

    matplotlib.pyplot.tight_layout()
    matplotlib.pyplot.savefig(f"graphAverage.png")

graphEach()
graphAverage()
