#include <stdio.h>

#define ARRAY_SIZE 10

enum STATUS {SUCCESS, ERROR};

int rotatedSort(int * ioData, const int iSize, const int pivot);

int main() {
    int arr[ARRAY_SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int pivot = 0;

    int returnStatus = rotatedSort(arr, ARRAY_SIZE, pivot);
    
    for(int i=0; i<ARRAY_SIZE; i++){
        printf("%d, ", arr[i]);
    }
    if(returnStatus){
        printf("Array not modified\n");
    }
    else{
        printf("Array sorted\n");
    }
    

    return 0;
}

int rotatedSort(int * ioData, const int iSize, const int iPivot){
    
    // validating arguments
    if(NULL==ioData){
        printf("[%s]:[%d] Array pointing to NULL\n", __func__, __LINE__);
        return ERROR;
    }

    if(0==iSize){
        printf("[%s]:[%d] Invalid iSize\n", __func__, __LINE__);
        return ERROR;
    }

    if(0>=iPivot || iPivot>iSize){
        printf("[%s]:[%d] Invalid pivot\n", __func__, __LINE__);
        return ERROR;
    }

    // sorting logic
    int index=0, indexSwap=0, indexData=0, tSwap, tIndex;
    for(index=0; index<iSize; index++){
        
        // calcualting nidex relative to pivot
        indexData = (index + iPivot - 1) % iSize;
        // indexData = index;

        for(indexSwap=0; indexSwap<iSize; indexSwap++){
            tIndex = (indexSwap + indexData)%iSize;
            printf("%d\t(%d)\t%d\t(%d)\n", ioData[indexData], indexData, ioData[tIndex], tIndex);
            
            // swaping data
            if(ioData[indexData] < ioData[tIndex]){
                tSwap = ioData[indexData];
                ioData[indexData] = ioData[tIndex];
                ioData[tIndex] = tSwap;
            }
        }
    }

    return SUCCESS;
}