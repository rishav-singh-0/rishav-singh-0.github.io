#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "random_str_gen.c"

enum STATUS {SUCCESS, ERROR};
#define STR_LEN 50
#define CAST(ch) (ch - '0')
#define CHAR_MULT(x, y) (CAST(x) * CAST(y))

int stringMultiply(const char*, const char*, char*, const int);

int main() {
    char num1[STR_LEN]; 
    char num2[STR_LEN];
    char result[2*STR_LEN];

    randomStr(num1, rand()%STR_LEN, 10, '0');
    printf("Input Num1: %s\n", num1);

    randomStr(num2, rand()%STR_LEN, 10, '0');
    printf("Input Num2: %s\n", num2);
    
    int returnStatus = stringMultiply(num1, num2, result, STR_LEN);
    printf("Multiplication of %s and %s is %s\n", num1, num2, result);
    
    return 0;
}

int stringMultiply(const char* iNum1, const char* iNum2, char * ioResult, const int maxLen){
    // validating arguments
    if(NULL==iNum1){
        printf("[%s]:[%d] iNum1 pointing to NULL\n", __func__, __LINE__);
        return ERROR;
    }
    if(NULL==iNum2){
        printf("[%s]:[%d] iNum2 pointing to NULL\n", __func__, __LINE__);
        return ERROR;
    }
    if(NULL==ioResult){
        printf("[%s]:[%d] ioResult pointing to NULL\n", __func__, __LINE__);
        return ERROR;
    }

    const int lenNum1 = strlen(iNum1)-1;
    const int lenNum2 = strlen(iNum2)-1;

    int indexNum1, indexNum2;
    // printf("%d\t%d", lenNum1, lenNum2);
    int sum = 0, carry = 0, charMul = 0, prev = 0;
    memset(ioResult, '0', lenNum1+lenNum2+2);
    
    for(indexNum2=lenNum2; indexNum2>=0; indexNum2--){
        
        carry = 0;
        for(indexNum1=lenNum1; indexNum1>=0; indexNum1--){
            prev = CAST(ioResult[indexNum1+indexNum2+1]);
            charMul = CHAR_MULT(iNum1[indexNum1], iNum2[indexNum2]);
            sum = carry + charMul + prev;
            carry = sum/10;
            sum -= carry*10;
            
            // printf("carry: %d\tsum: %d\tcharMul: %d\tprev: %d\n", carry, sum, charMul, prev);
            ioResult[indexNum1+indexNum2+1] = (sum) + '0';
        }
        ioResult[indexNum1+indexNum2+1] = (carry) + '0';
        // printf("\n");
    }
    
    // NULL termination of ioResult string
    ioResult[lenNum1+lenNum2+2] = '\0';
    
    return SUCCESS;
    
}
