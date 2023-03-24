#include <stdio.h>
#include <string.h>

typedef struct st_database{
    float num;
    char account_num[20];
}st_database;

typedef struct st_card{
    float num;
    char account_num[20];
}st_card;

//introduce data base
st_database server_db [20]={
    {5000.0, "607833656635906773"},
	{4000.5, "005768153188661175"},
	{3000.2, "075982963293069095"},
	{2000.12, "611153338528212031"}
};

int search_db(st_card * card  ){
    for(int i=0 ;i<20;i++)
    if(strcmp(card->account_num,server_db[i].account_num)==0){
        return i; // no of hte transaction
    }
    return -1; //not found
}

int main(){
    st_card card ={3000.2, "07592963293069095"};
    int x =search_db(&card);

    if(x==-1){
        printf("not found stolen card");
    }
    else{
        printf("Transaction done");
    }

    return 0;
}