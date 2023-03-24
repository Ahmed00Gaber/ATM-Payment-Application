/******************************************************************************
longest job first algorithm
*******************************************************************************/
#include <stdio.h>

int main()
{
    int procs, bst_time[10],ariv_time[10],temp,waiting_time=0,turnaround=0,copy[10],postion[10],count,x=0;
    printf("please enter no of processes: ");
    scanf("%d",&procs);
    
    //ask user to enter  burst time
    printf("please enter burst-time of each processes:\n");
    for(int i=0 ;i<procs;i++){
    printf("P[%d]: ", i+1);
    scanf("%d",&bst_time[i]);
    copy[i]=bst_time[i];
    }
    printf("\n");
    
    //sorting algorithm for burst-time
    temp=bst_time[0];//largest number
    for(int i=0 ;i<procs;i++){
        for(int j=0 ;j<procs;j++){
            if(bst_time[i]>bst_time[j]){
                temp=bst_time[i];
                bst_time[i]=bst_time[j];
                bst_time[j]=temp;

            }
        }
    }
    //ordering elements
    for(int i=0 ;i<procs;i++){
        count=0;
        for(int j=0 ;j<procs;j++){
            if(copy[i]==bst_time[j]){
                count=j+1; // due to we print our processes from 1
                postion[x]=count;
                x++;
            }
        }
    }
    //printing the gantt schart processes
    int tot_waiting=0;
    printf("process   turnaround  waiting_time\n");
    for(int i=0 ;i<procs;i++){
    turnaround=turnaround+bst_time[i];
    if(i>=1){//to start 1st with zero then after 
    waiting_time=turnaround-bst_time[i];
    tot_waiting=tot_waiting+waiting_time;
    } 
    printf("p[%d]:      %d            %d\n",postion[i],turnaround,waiting_time);
    }
	printf("\nAv.waiting Time = %f",(double)tot_waiting/procs);
    printf("\nAv.turnaround Time = %f",(double)turnaround/procs);
    return 0;
}
