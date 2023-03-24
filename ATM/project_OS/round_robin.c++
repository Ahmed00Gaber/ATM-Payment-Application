/******************************************************************************
Queue using array
we used c++ to be able to use bool not in c should be done using enum
Creating a structure gives the programmer the provision to declare multiple variables
of different data types treated as a single entity.
*******************************************************************************/
#include <iostream>

using namespace std;

const  int capcity=10;
int waiting_time;

//struct 
struct Queue{
    int arr[capcity];
    int front =-1;
    int rear =-1;
    
    bool isempty(){
        if(front==-1 && rear==-1) return true;
        else return false;
    }
    bool isFull(){
        if(rear== capcity -1) return true;
        else return false;
    }
    void enqueue(int val){
        if(isFull()) return; //go out
        
        else if(isempty()){
            front=rear=0;  //start from 0
        }
        else rear++;
        arr[rear]=val;
    }
    void dequeue(){
        if(isempty()) return ;
        else if(front==rear){ //last element
            front=rear= -1;
        }
        else front++;
    }
    int front_val(){
        if(isempty()) return -1;
        else{
            return arr[front];
        }
    }
};
int bst_time[10];
int main()
{   
    Queue q; //create object
    int n,x; 
    
    cout << "Type a number of processes: ";
    cin >> n; 
    
    // entering burst time
    cout << "Type the burst time:\n";   
    for(int i=0;i<n;i++){
       cout << "p["<<i+1<<"]: ";
       cin >> x; 
       bst_time[i]= x;
       //enqueue the given data in the queue
       q.enqueue(x);
    }
   
//Note count inc counter move then limited opposite counter to not exceed process value
    cout << "\nGuantt schart:\n";
    cout << "process:   \n";
    int qtm_time =4;
    int t,count=0,opp_count=n,total=0;
    //concerns turnaound
    int arr[10],arr_count[10],arr_wait[10],counter2=0;
    while(!q.isempty()){ //while not all element is dequeded
        //check if the value of process is less than the quntum time
        if(qtm_time>q.front_val()){
            //change process 
            count++;
            //sum the value of the process
            total=total+q.arr[q.front];
            //value is no longer used in queue 
            q.arr[q.front]=0;
            arr[counter2]=total;
            arr_count[counter2]=count;
            counter2++;
            cout << "[p"<< count<<"]\t";
            //dequeue it and never put it back
            q.dequeue();
            //prevent count to exceed no of process in the queue 
            if(count>=opp_count) count=0;
            opp_count--;
        }
        else{
            //subtract qtm_time from the process time
          t= q.arr[q.front] - qtm_time;
          //if process finished
          if(q.arr[q.front]==0){
              //find turn around of each process
              arr[counter2]=total;
              //related for count of process
              arr_count[counter2]=count;
              counter2++;
              
              
          }
          //count increase to change process in queue
          count++;
          //change value after subtracting in array
          q.arr[q.front]=t;
          // summ the value to the one before
          total=total+qtm_time;
          cout << "[p"<< count<<"]\t";
          //deequeue it   
          q.dequeue();
          //enqueue it again in the queue
          q.enqueue(t);
          //prevent count to exceed no of process in the queue 
          if(count>=opp_count) count=0;
        }
    }
    
    //sorting them
    int temp=arr_count[0];
    int temp2;
    for(int i=0 ;i<n;i++){//ordering from smallest to largest
        for(int j=0 ;j<n;j++){
            if(arr_count[i]<arr_count[j]){
                temp=arr_count[i];
                temp2=arr[i];
                arr_count[i]=arr_count[j];
                arr[i]=arr[j];
                arr_count[j]=temp;
                arr[j]=temp2;
            }
        }
    }
    

    
    cout << "\n\nprocess \tturnaround\twaiting_time\n";
    int tot_waiting=0;
    for(int i=0 ;i<n;i++){
        waiting_time= arr[i]-bst_time[i];
        tot_waiting =tot_waiting+waiting_time;
       cout <<"[p"<<arr_count[i]<<"]\t\t" << arr[i]<<"\t\t"<<waiting_time<<"\n"; 
    }

    printf("\nAv.waiting Time = %f",(double)tot_waiting/n);
    printf("\nAv.turnaround Time = %f",(double)total/n);
    return 0;
}





