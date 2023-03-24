#include <stdio.h>
#include <string.h>

#include "../ATM.h"

// uint8_t cardHolderName[25];
// uint8_t primaryAccountNumber[20];
// uint8_t cardExpirationDate[6];


DateError checkDay(int day){
    if(day<1 || day>30){
        return WRONG_DAY;
    }
    return OK_DATE;
}

/* Validate Month 1 -> 12  */
DateError checkMonth(int month){
    if(month<1 || month>12){
        return WRONG_MONTH;
    }
    return OK_DATE;
}

//defing a function with enumn means your return is one of enum
EN_cardError_t getCardHolderName(ST_cardData_t* cardData){
    printf("please enter your name: ");
    scanf("%[^\n]%*c\n", cardData->cardHolderName); // input from a user with space
    if((strlen(cardData->cardHolderName)==0) || (strlen(cardData->cardHolderName)< NAME_MIN) || 
    (strlen(cardData->cardHolderName)>NAME_MAX) ){
        printf("WRONG NAME \n");
        return WRONG_NAME;
    }
    return OK_CARD;
}

/* This function will ask for the card's Primary Account Number */
EN_cardError_t getCardPAN(ST_cardData_t* cardData){
    printf("\nplease enter your account number: ");
    scanf("%s", cardData->primaryAccountNumber);

    if((strlen(cardData->primaryAccountNumber)== 0) || (strlen(cardData->primaryAccountNumber)>CARD_MIN) ||
    (strlen(cardData->primaryAccountNumber)<CARD_MAX)){ 
        return WRONG_PAN;
    }
    return OK_CARD;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
    printf("\nplease enter your exp date , e.g 05/25: ");
    scanf("%s", cardData->cardExpirationDate);
    //convert date and month to int
    int month = ((int)(cardData->cardExpirationDate[0]-'0'))*10 + (int)(cardData->cardExpirationDate[1]-'0');
    int day = ((int)(cardData->cardExpirationDate[3]-'0'))*10 + (int)(cardData->cardExpirationDate[4]-'0');

    if((strlen(cardData->cardExpirationDate)== 0) || (strlen(cardData->cardExpirationDate)!=EXPIRE_LEN)){ 
        printf("WRONG EXP DATE\n");
        return WRONG_EXP_DATE;
    }
    else if(checkMonth(month)){
        printf("WRONG EXP DATE\n");
        return WRONG_EXP_DATE;
    }
    else if(checkDay(day)){
        printf("WRONG EXP DATE\n");
        return WRONG_EXP_DATE;
    }
    return OK_CARD;
}

int main(){
    return 0;
}

