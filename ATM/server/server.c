#include <stdio.h>
#include <string.h>

#include "../ATM.h"


// typedef struct ST_transaction_t
// {
// 	ST_cardData_t cardHolderData;
// 	ST_terminalData_t terminalData;
// 	EN_transState_t transState;
// 	uint32_t transactionSequenceNumber;
// }ST_transaction_t;

/* Using this website https://www.dcode.fr/luhn-algorithm to generate Luhn Numbers */
extern ST_accountsDB_t serverDatabase[MAX_SERVER] = {//extern search for it's value outside main 1st in folder then in other folders
    //each of this data is an array
	{5000.0, "607833656635906773"},
	{4000.5, "005768153188661175"},
	{3000.2, "075982963293069095"},
	{2000.12, "611153338528212031"},
	{1000.334, "910398034808780349"},
	{1002.4, "053325461606192194"},
	{999.2, "742772749714646812"},
	{324.2, "209325396074423440"},
	{1231.4, "851079961065873585"},
	{1253.4, "442875351414250640"},
	{5123.5, "615903891876676888"},
	{6345.1, "59022961351481653"},
	{6345.6, "91119474574056192"},
	{1241.7, "89928622813608190"},
	{4761.3, "78687103102360615"},
	{125.7, "8316351323704972"},
	{214.6, "5006447651585560"},
	{1251.3, "3870771107430131"},
	{151.6, "0354025546355735"}
};

//defining an empty array of struct to save all transaction
// with having all members of stucrt which each has it's own members
extern ST_transaction_t transactionDatabase[MAX_TRANSACTION] = { 0 };

/* cardTemp use as a buffer to transfer data */
ST_cardData_t cardTemp; //defing an object of struct for card data

int sequenceNumber=0;
int accountOffset = 0; //no of the client in the database

/* This fanction use to search about the account 
using string compare if it returns 0 , means they are the  same
so the function return the INDEX of the account in the database array */
//zz
int searchAccount(ST_cardData_t* cardData)
{
	for (int i = 0; i < MAX_SERVER; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, serverDatabase[i].primaryAccountNumber) == 0)
		{
			return i;
		}
	}
	return -1;
}

//we have to define struct to be able to put it that's why we used struct temp
//zz
EN_serverError_t isValidAccount(ST_cardData_t* cardData){
   cardTemp = *cardData;;
    // num of client in the database to use it in other function directly without need to search again
    accountOffset=searchAccount(cardData);
    if(accountOffset== -1)
	{
		printf("DECLINED STOLEN CARD \n");
        return DECLINED_STOLEN_CARD;
    }
	else
	{
    return OK;
	}
}

//function on enumration state
EN_transState_t recieveTransactionData(ST_transaction_t* transData){
    // passing struct address to the function
	if (isValidAccount(&(transData->cardHolderData))) 
	{
		printf("DECLINED STOLEN CARD \n");
		//change the transState in each database
		transactionDatabase[sequenceNumber].transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&(transData->terminalData))) //pointer ==1 wrong name
	{
		printf("DECLINED INSUFFECIENT_FUND\n");
		//change the transState in each database
		transactionDatabase[sequenceNumber].transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	//we need all of the struct so we don't need to pass address
	else if (saveTransaction(transData)) 
	{
		printf("INTERNAL SERVER_ERROR \n");
		//change the transState in each database
		transactionDatabase[sequenceNumber].transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else
	{	//update the new balance of the system in the database
		serverDatabase[accountOffset].balance-= transData->terminalData.transAmount ;
		//printf new balance after subtraction
		printf("your new balance is: %f\n",serverDatabase[accountOffset].balance);
		transactionDatabase[sequenceNumber].transState = APPROVED;
		return APPROVED;
	}
}

//zz
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData){
    //account offest is client number in database we search direclty for it
	if(termData->transAmount > serverDatabase[accountOffset].balance)
	{ 
        printf("low balance \n");
        return LOW_BALANCE;
    }
    return OK;
}
//z
EN_serverError_t saveTransaction(ST_transaction_t* transData){
	if (sequenceNumber<255){
		//save the value of transaction in the empty database
		//according to رقم العملية
		transactionDatabase[sequenceNumber] = *transData;
		//here the sequence num is not saved yet so we should save it in
		//the member transactionSequenceNumber of struct
		transactionDatabase[sequenceNumber].transactionSequenceNumber = sequenceNumber;
		transactionDatabase[sequenceNumber].transState = APPROVED;
		sequenceNumber++;
		return OK;
	}
	printf("transaction failed \n");
	return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	for (uint8_t i = 0; i < sequenceNumber; i++)
	{
		if (transactionDatabase[i].transactionSequenceNumber == transactionSequenceNumber)
		{
            //return it's sequence number (tranaction num)
			*transData = transactionDatabase[i];
			return OK;
		}
	}
	printf("TRANSACTION NOT FOUND \n");
	return TRANSACTION_NOT_FOUND;
}


int main(){
	return 0;
}