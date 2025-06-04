#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * Arguments:
 - ioStrPtr: string pointer
 - iLen: length of the required string
 - iRange: range of each characters
 - iOffset: first character of the range

  Example:
    randomStr(arr, 10, 26, 'a');
    output: "cekcqbkjrx"
*/
void randomStr(char ioStrPtr[], int iLen, int iRange, int iOffset) {
    
    // validating arguments
    if(NULL==ioStrPtr){
        fprintf(stderr, "[%s]:[%d] ioStrPtr pointing to NULL\n", __func__, __LINE__);
        return;
    }
    if(iLen<1){
        fprintf(stderr, "[%s]:[%d] iLen is less than 1\n", __func__, __LINE__);
        return;
    }
    
    // NULL termination of string
    ioStrPtr[iLen-1] = '\0';
    
    // range validation
    if(0==iRange){
        fprintf(stderr, "[%s]:[%d] iRange could not be 0 (Divide by 0 detected)\n", __func__, __LINE__);
        return;
    }
    
    srand(time(0));
    while(iLen>0){
        iLen--;
        ioStrPtr[iLen] =  (rand() % iRange) + iOffset;
        // printf("%d", ioStrPtr[iLen]);
    }
}
