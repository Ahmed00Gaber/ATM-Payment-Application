/******************************************************************************
priorety algorithm
Note: In this algorithm, I  assumed arrival times as 0, so turn around and completion times are same. 
*******************************************************************************/
#include <stdio.h>

int main()
{
    int procs, bst_time[10],priorety[10],temp,waiting_time=0,turnaround=0,copy[10],postion[10],count,x=0;
    printf("please enter no of processes: ");
    scanf("%d",&procs);
    
    //ask user to enter  burst time
    printf("please enter burst-time of each processes:\n");
    for(int i=0 ;i<procs;i++){
    printf("P[%d]: ", i+1);
    scanf("%d",&bst_time[i]);
    }
    
    //ask user to enter  priorety
    printf("please enter priorety of each processes:\n");
    for(int i=0 ;i<procs;i++){
    printf("P[%d]: ", i+1);
    scanf("%d",&priorety[i]);
    copy[i]=priorety[i];
    }
    printf("\n");
    
    //sorting algorithm for burst-time
    temp=priorety[0];//smallest number
    for(int i=0 ;i<procs;i++){
        for(int j=0 ;j<procs;j++){
            if(priorety[i]<priorety[j]){
                temp=priorety[i];
                priorety[i]=priorety[j];
                priorety[j]=temp;
            }
        }
    }
    //ordering elements
    //this approach is done by comparing value for copy with the new value for positioning 
    for(int i=0 ;i<procs;i++){
        count=0;
        for(int j=0 ;j<procs;j++){
            if(copy[i]==priorety[j]){
                count=j+1;
                postion[x]=count;
                x++;
            }
        }
    }
    //printing the gantt schart processes
    int tot_waiting=0;
    printf("process   turnaround  waiting_time\n");
    for(int i=0 ;i<procs;i++){
    turnaround=turnaround+bst_time[postion[i]-1];
    if(i>=1){//to start 1st with zero then after 
    waiting_time=turnaround-bst_time[postion[i]-1]; //-1 bec position start from 1
    tot_waiting=tot_waiting+waiting_time;
    }
    printf("p[%d]:      %d            %d\n",postion[i],turnaround,waiting_time );
    }
	printf("\nAv.waiting Time = %f ",(double)tot_waiting/procs);
	printf("\nAv.turnaround Time = %f ",(double)turnaround/procs);
    return 0;
}
