#include <stdio.h>
  
int main() 
{
      int arrival_time[10], bst_time[10], temp[10], i, shortest, num = 0, x, procs;
      float tot_wait = 0, tot_turnaround = 0, comp_time , waiting=0 ,turnaround=0;
     
      printf("please enter no of processes: ");
      scanf("%d", &procs); 
      printf("\nEnter Details of %d Processes:", procs);
      for(i = 0; i < procs; i++)
      {
            printf("\nEnter Arrival Time:");
            scanf("%d", &arrival_time[i]);
            printf("\nEnter Burst Time:");
            scanf("%d", &bst_time[i]); 
            temp[i] = bst_time[i];
      }
      //assume last element is the smallest
      bst_time[8] = 100; //100 is max size of burst time
      printf("process   turnaround  \twaiting_time\n");
      for(x = 0; num != procs; x++)//num nomber of process done  if all process done don't join
      {
            shortest = 8;//found shortest element
            for(i = 0; i < procs; i++)
            {   
                  if((arrival_time[i] <= x ) && ( bst_time[i] < bst_time[shortest] )&& (bst_time[i] > 0))// <x to check the smallest arrival time each time
                  {
                        shortest = i;
                  }
            }
            bst_time[shortest]=bst_time[shortest]-1;
            if(bst_time[shortest] == 0)
            {
                  num++;
                  comp_time = x + 1; //compeletion time
                  //equation for turnaround
                  turnaround=  comp_time - arrival_time[shortest];
                  waiting =  turnaround - temp[shortest];
                  
                  tot_wait = tot_wait + comp_time - arrival_time[shortest] - temp[shortest];
                  tot_turnaround = tot_turnaround + comp_time - arrival_time[shortest];
                  printf("p[%d]:      %2f         %2f\n",shortest,turnaround,waiting);
            }
      }
      
      printf("\nAv.waiting Time:%lf", (double)tot_wait / procs);
      printf("\nAv.turnaround Time:%lf", (double)tot_turnaround / procs);
      return 0;
}