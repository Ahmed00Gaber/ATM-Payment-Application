#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../ATM.h"

// typedef struct ST_terminalData_t
// {
// 	float transAmount;
// 	float maxTransAmount;
// 	uint8_t transactionDate[11];
// }ST_terminalData_t;

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

int checkSum(long int creditCard, int length) {
    int i=0;
    int temp=0;
    int first=0;
    int second=0;
    int final=0;

    while(creditCard){
        if (i%2 != 0) {
            first = ((creditCard%10)*2);
            if (first>9){
                while(first){
                    temp += first%10;
                    first /= 10;
                }
            }
            temp += first;
        } else {
            second += creditCard%10;
        }
        creditCard /= 10;
        i++;
    }

    temp += second;

    final = temp%10;

    if (final == 0){
        return 1;
    }

    return 0;
}

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    printf("please enter your exp date , e.g 05/25/2020: ");
    scanf("%s", termData->transactionDate);
    int month = ((int)(termData->transactionDate[0]-'0'))*10 + (int)(termData->transactionDate[1]-'0');
    int day = ((int)(termData->transactionDate[3]-'0'))*10 + (int)(termData->transactionDate[4]-'0');

    if((strlen(termData->transactionDate)== 0) ||  (strlen(termData->transactionDate)!=TRANSACTION_LEN) || 
    (termData->transactionDate[2]!='/') || (termData->transactionDate[5]!='/')){ //still size not included
        printf("wrong Date \n");
        return WRONG_DATE;
    }
    else if(checkMonth(month)){
        printf("WRONG DATE \n");
        return WRONG_DATE;
    }
    else if(checkDay(day)){
        printf("WRONG DATE \n");    
        return WRONG_DATE;
    }
    return OK_TERMINAL;
}

//compare each day, month, year
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t  termData){ //not it's not a pointer to struct
    
    int day_c=((int) cardData.cardExpirationDate[0]-'0')*10 +((int) cardData.cardExpirationDate[1]-'0');
    int day_t=((int)  termData.transactionDate[0]-'0')*10 +((int)  termData.transactionDate[1]-'0');
    
    int month_c =((int) cardData.cardExpirationDate[3]-'0')*10 +((int) cardData.cardExpirationDate[4]-'0');
    int month_t =((int)  termData.transactionDate[3]-'0')*10 +((int)  termData.transactionDate[4]-'0');
    //1 card date
    int year_c= ((int) cardData.cardExpirationDate[5]-'0')*1000 +((int) cardData.cardExpirationDate[6]-'0')*100 + 
    ((int) cardData.cardExpirationDate[7]-'0')*10 +((int) cardData.cardExpirationDate[8]-'0');
    
    int year_t= ((int) termData.transactionDate[5]-'0')*1000 +((int) termData.transactionDate[6]-'0')*100 + 
    ((int) termData.transactionDate[7]-'0')*10 +((int)termData.transactionDate[8]-'0');

    // year and month of card should be bigger
    if(year_c >= year_t &&  month_c>=month_t ){ //is good
        //if both monthes is equal check day
        if(month_c == month_t && day_c<day_t){
                return EXPIRED_CARD;
        }
        return OK_TERMINAL;
    }
    else {
    return EXPIRED_CARD;
    }
}

//done
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData){
    char *ptr;
    //strtol convet string to long int
    long int result =strtol(cardData->primaryAccountNumber, &ptr, 10); 
    //the returned reult is but in check
    int check= checkSum(result,strlen(cardData->primaryAccountNumber));
    if(check==0){
        printf("invalid card");
        return INVALID_CARD;
    }
    return OK_TERMINAL;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData){
    printf("pleaser enter the required transaction amount: ");
    scanf("%2f",&(termData->transAmount));
    if(termData->transAmount <= 0){
        printf("invalid amount");
        return INVALID_AMOUNT;
    }
    return OK_TERMINAL;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
    if(termData->transAmount > termData->maxTransAmount){
        printf("EXCEED MAX AMOUNT \n");
        return EXCEED_MAX_AMOUNT;
    }
    return OK_TERMINAL;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData){
    printf("pleaser enter the required transaction amount: ");
    scanf("%2f",&(termData->maxTransAmount));

    if(termData->transAmount <= 0){
        printf("invalid max amount");
        return INVALID_MAX_AMOUNT;
    }
    return OK_TERMINAL;
}

