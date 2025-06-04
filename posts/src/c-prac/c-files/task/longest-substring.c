#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "random_str_gen.c"

#define ARRAY_SIZE 100

int getLongestSubstring(const char * iStrPtr, int iLen, int * ioStartIdx);

int main() {
    
    char string[ARRAY_SIZE];
    randomStr(string, rand()%ARRAY_SIZE, 26, 'a');
    printf("Input string: %s\n", string);

    int startIdx = 0;
    int subStringLen = getLongestSubstring(string, strlen(string), &startIdx);
    
    printf("subSrLen = %d \nstartIdx = %d\n", subStringLen, startIdx);
    printf("%.*s\n", subStringLen, (string + startIdx));

    return 0;
}

int getLongestSubstring(const char * iStrPtr, int iLen, int * ioStartIdx)
{
    // validating arguments
    if(NULL==iStrPtr){
        printf("[%s]:[%d] iStrPtr pointing to NULL\n", __func__, __LINE__);
        exit(1);
    }
    if(NULL==ioStartIdx){
        printf("[%s]:[%d] ioStartIdx pointing to NULL\n", __func__, __LINE__);
        exit(1);
    }
    if(0==iLen){
        printf("[%s]:[%d] iLen is 0\n", __func__, __LINE__);
        exit(1);
    }
    if(1==iLen){
        *ioStartIdx = 0;
        return 1;
    }
    
    char tPtr=0, maxSubStrLen=0, subStrLen=0;
    *ioStartIdx = 0;

    int indexIter1 = 0, indexIter2 = 0; 
    for(indexIter1=0; indexIter1<iLen; indexIter1++){
        
        // comparing current char with all previous chars
        for(indexIter2=tPtr; indexIter2<indexIter1; indexIter2++){
            // printf("%c %c, ", iStrPtr[indexIter2], iStrPtr[indexIter1]);
            // printf("\t\t\tI1=%d\tI2=%d\tsubLen=%d\tptr=%d\n", indexIter1, indexIter2, subStrLen, tPtr);

            // changing tPtr to latest equal char
            if(iStrPtr[indexIter1]==iStrPtr[indexIter2]){
                tPtr = indexIter2+1;
                subStrLen = indexIter1 - indexIter2;
                // printf("%d, %d\n", subStrLen, tPtr);
                break;
            }
            subStrLen++;
            // printf("len=%d, ptr=%d\n", subStrLen, tPtr);
        }
        if(maxSubStrLen < subStrLen){
            maxSubStrLen = subStrLen;
            *ioStartIdx = tPtr;
        }
        subStrLen = 1;
    }

    return maxSubStrLen;
}
