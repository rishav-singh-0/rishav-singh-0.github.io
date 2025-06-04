#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcMove(const int iNumArr[], const int iArrLen, const int k);

int main() {
    // int nums[] = {1, 0, 0, 1, 0, 1}; 
    // int k = 2;  // 1
    int nums[] = {1, 0, 0, 0, 0, 0, 1, 1}; 
    int k = 3;  // 5
    // int nums[] = {1, 1, 0, 1}; 
    // int k = 2;  // 0
    
    int moves = calcMove(nums, sizeof(nums)/sizeof(int), k);
    printf("Moves taken: %d\n", moves);
    return 0;
}


int calcMove(const int iNumArr[], const int iArrLen, const int k){
    
    // validating arguments
    if(NULL==iNumArr){
        fprintf(stderr, "[%s]:[%d] ioStrPtr pointing to NULL\n", __func__, __LINE__);
        exit(0);
    }
    if(iArrLen<=0){
        fprintf(stderr, "[%s]:[%d] iArrLen is not valid\n", __func__, __LINE__);
        exit(0);
    }
    if(0 == k){
        return 0;
    }
    
    int minMoves = iArrLen;
    

    // calculate largest pair
    // return 0 if largest pair is more than k
    // if k > largest pair store starting and ending of largest pair
    
    int maxSameLen=0, startPtr=0, endPtr=0;
    int detect[2] = {0, 0};
    int *arrPtr = calloc(iArrLen, sizeof(int));
    
    int index1, index2 = 0, prev = iNumArr[0];
    for(index1 = 0; index1<iArrLen; index1++){
        if(prev != iNumArr[index1]){
            index2++;
            prev = iNumArr[index1];
        }
        if(0 < iNumArr[index1]){
            detect[0] = 0;
            detect[1]++;
            arrPtr[index2]+=1;
        }
        else{
            detect[0]--;
            detect[1] = 0;
            arrPtr[index2]--;
        }
        if(arrPtr[maxSameLen] < detect[1]){
            maxSameLen = index2;
        }
        // printf("%d%d, ", detect[0], detect[1]);
    }
    
    // printf("MaxLen: %d\n", maxSameLen);
    if(k <= arrPtr[maxSameLen]){
        return 0;
    }

    // memory reduction
    const int arrLen = index2;
    arrPtr = realloc(arrPtr, sizeof(int)*arrLen);

    // printf("\n");
    index2 = 0;
    
    // finding first positive number
    for(index1 = 0; index1<arrLen; index1++){
        if(arrPtr[index1]>0)
            break;
    }
    int prev1 = index1;
    int moves = iArrLen;
    for(index1+1; index1<arrLen+1; index1++){
        // printf("%d ", arrPtr[index1]);
        
        if(arrPtr[index1]>0){
            moves = -1 * arrPtr[index1-1];
        }
        if(moves < minMoves){
            minMoves = moves;
        }
        // printf("Moves: %d, %d\n", moves, arrPtr[index1]);
    }

    // freeing dynamic memory
    free(arrPtr);
    arrPtr = NULL;
    return moves;
    
}