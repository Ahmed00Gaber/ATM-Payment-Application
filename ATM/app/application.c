#include <stdio.h>

#include "../ATM.h"


//declaration

void appStart(void){

    //declaration for structs 
    ST_transaction_t transactionData;
    ST_cardData_t *cardData = &transactionData.cardHolderData;
    ST_terminalData_t *termData = & transactionData.terminalData;

    /* card side*/
    while (getCardHolderName(cardData)); // >0
	  while (getCardExpiryDate(cardData));
	  while (getCardPAN(cardData));

    /* term side*/
    while(getTransactionDate(termData));
    if (isCardExpired(*cardData, *termData))
      return;
    if (isValidCardPAN(cardData))
		  return;

    while(getTransactionAmount(termData));
    while(setMaxAmount(termData));
    if (isBelowMaxAmount(termData))
		  return;

    /* server side*/
    if(recieveTransactionData(&transactionData))
		return;

    return ;
}

int main(){
  appStart();
}