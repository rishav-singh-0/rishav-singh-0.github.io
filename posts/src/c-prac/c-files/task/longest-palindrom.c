#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "random_str_gen.c"

#define ARRAY_SIZE 100
typedef enum BOOLEAN{false, true} bool;

int longestPalindrome(const char*, int, int*);
bool isPalindrome(const char*, int iLen);

int main() {
    char string[ARRAY_SIZE];
    randomStr(string, rand()%ARRAY_SIZE, 26, 'a');
    printf("Input string: %s\n", string);

    int startIdx = 0;
    int palinLen = longestPalindrome(string, strlen(string), &startIdx);
    
    printf("Max Palindrome Len = %d\n", palinLen);
    printf("%.*s\n", palinLen, (string + startIdx));
    return 0;
}

int longestPalindrome(const char * iStringPtr, int iLen, int * ioStartIdx) {
    // validating arguments
    if(NULL==ioStartIdx){
        printf("[%s]:[%d] ioStartIdx pointing to NULL\n", __func__, __LINE__);
        return 0;
    }
    if(NULL==iStringPtr){
        *ioStartIdx = 0;
        printf("[%s]:[%d] iStrPtr pointing to NULL\n", __func__, __LINE__);
        return 0;
    }
    if(1==iLen){
        *ioStartIdx = 0;
        return 1;
    }

    int maxPalinLen = 1;
    *ioStartIdx = 0;
    // isPalindrome(iStringPtr, iLen);
    
    int indexIter = 0;
    int len = 0, startIdx = 0, palinLen=1;
    bool isPalin = false, moveForward1=true, moveForward2=true;
    for(indexIter=0; indexIter < iLen; indexIter++){
        moveForward1=true, moveForward2=true;
        for(len=0; (moveForward1|moveForward2) && (indexIter-len >= 0) && (indexIter+len <= iLen); len++){
            startIdx = indexIter - len;
            // printf("%d\n", len);
            
            if(moveForward1 && startIdx>=0 && len > 0){
                isPalin = isPalindrome((iStringPtr + startIdx), 2*len);
                // printf("Even: %d : %.*s\n",isPalin, 2*len, (iStringPtr + startIdx));
                if(isPalin){
                    palinLen = 2*len;
                }
                else{
                    moveForward1 = false;
                }
            }

            if(moveForward2 && indexIter + len < iLen){
                isPalin = isPalindrome((iStringPtr + startIdx), 2*len+1);
                // printf("Odd : %d : %.*s\n", isPalin, 2*len+1, (iStringPtr + startIdx));
                if(isPalin){
                    palinLen = 2*len+1;
                }
                else{
                    moveForward2 = false;
                }
            }
            
            if(palinLen > maxPalinLen){
                maxPalinLen = palinLen;
                *ioStartIdx = startIdx;
            }

        }
        // printf("\n");
    }

    return maxPalinLen;
}

bool isPalindrome(const char* iStrPtr, int iLen){
    
    // validating arguments
    if(NULL==iStrPtr){
        printf("[%s]:[%d] iStrPtr pointing to NULL\n", __func__, __LINE__);
        return false;
    }
    if(1==iLen){
        return true;
    }

    int index = 0;
    int maxIter = iLen/2;
    bool result = true;
    // printf("%.*s : %d\n", iLen, iStrPtr, iLen);
    for(index=0; index<maxIter; index++){
        // printf("\nPalindrome: %d:%c\t%d:%c\n", index, iStrPtr[index], iLen-index-1, iStrPtr[iLen-index-1]);
        if(iStrPtr[index]!=iStrPtr[iLen-index-1]){
            result = false;
        }
    }
    // printf("Result: %d\n", result);
    
    return result;
}
