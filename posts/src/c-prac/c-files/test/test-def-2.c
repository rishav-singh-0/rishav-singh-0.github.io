#include <stdio.h>
#include <string.h>

void convertStr(const unsigned int iNum, char ioStrPtr[]);

int main() {
    unsigned int num = 1234567;
    char result[100];

    convertStr(num, result);
    puts(result);
    return 0;
}

void convertStr(const unsigned int iNum, char ioStrPtr[]){
    
    // validating arguments
    if(NULL==ioStrPtr){
        fprintf(stderr, "[%s]:[%d] ioStrPtr pointing to NULL\n", __func__, __LINE__);
        return;
    }
    if(iNum<0){
        fprintf(stderr, "[%s]:[%d] iLen is less than 0\n", __func__, __LINE__);
        *ioStrPtr = 0;
        return;
    }
    
    // NULL termination of string
    ioStrPtr[0] = '\0';
    
    const char* ones[10] = {"Zero", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine "};
    const char* teens[10] = {"Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fiveteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
    const char* tens[10] = {"", "Ten ", "Twenty ", "Thirty ", "Fourty ", "Fivety ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};
    const char* zeros[5] = {"", "Hundred ", "Thousand ", "Million ", "Billion "};
    
    if(iNum==0){
        strcpy(ioStrPtr, ones[0]);
        return;
    }

    char strHundreds[100];
    char strHolder[100];
    
    int num = iNum;
    int rem=0, places=0;
    unsigned short int threeDigits = 0, thirdPlace = 0, secondsPlace=0, onesPlace=0;
    while(num>0){
        threeDigits = num%1000;
        // printf("%d\t", threeDigits);
        num = num/1000;
        
        *strHundreds = '\0';
        // Resolving 3 digits
        if(threeDigits>0){
            places++;
            thirdPlace = threeDigits/100;
            threeDigits = threeDigits%100;
            secondsPlace = threeDigits/10;
            onesPlace = threeDigits%10;
            // printf("%d %d %d\n", thirdPlace, secondsPlace, onesPlace);
            if(thirdPlace>0){
                sprintf(strHundreds, "%s%s", ones[thirdPlace], zeros[1]);
            }
            if(secondsPlace>1){
                strcat(strHundreds, tens[secondsPlace]);
            }
            else if (secondsPlace == 1){
                strcat(strHundreds, teens[onesPlace]);
            }
            if(onesPlace>0 && secondsPlace != 1){
                strcat(strHundreds, ones[onesPlace]);
            }
        }
        
        // printf("Places: %d \n", places);
        if(places==1){
            // puts(strHundreds);
            sprintf(ioStrPtr, "%s", strHundreds);
        }
        else if(places>1){
            sprintf(strHolder, "%s%s%s", strHundreds, zeros[places], ioStrPtr);
            // puts(strHolder);
            strcpy(ioStrPtr, strHolder);
            
        }

    }
    
}
