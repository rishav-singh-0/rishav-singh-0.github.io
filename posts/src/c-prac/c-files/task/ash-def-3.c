#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PALIN_LEN 5

typedef enum{false, true} bool;


bool isPalindrome(const char* iStrPtr, int iLen);
void searchPalin(const char* iStrPtr, int iLen, const int maxPalin, int* ioCount);

int main() {
    char str[] = "1033010";
    int result = 0;
    searchPalin(str, strlen(str), PALIN_LEN, &result);
    printf("Result: %d\n", result);
    return 0;
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

void searchPalin(const char* iStrPtr, int iLen, const int maxPalin, int* ioCount){
    char *strPtr = (char *)malloc(sizeof(char)*iLen);
    memcpy(strPtr, iStrPtr, sizeof(char)*iLen);
    
    for(int i =0; i<= iLen-5; i++){
        if(isPalindrome(strPtr+i, maxPalin)){
            *ioCount += 1;
        }
    }
    for(int j=iLen; j >= 0; j--){
        printf("%d ", j);
        memcpy(strPtr+j, iStrPtr+j+1, sizeof(char)*iLen-j);
        puts(strPtr);
    }

    free(strPtr);
    strPtr = NULL;
    
}