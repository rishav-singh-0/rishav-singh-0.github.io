#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int medSubArr(const int iArr[], int iLen, const int iMedian);

int main() {
    int arr[] = {3,2,1,4,5};
    int k=4;
    
    int result = medSubArr(arr, sizeof(arr)/sizeof(int), k);
    return 0;
}

int medSubArr(const int iArr[], int iLen, const int iMedian){
    
    // validating arguments
    if(NULL==iArr){
        printf("[%s]:[%d] iArr pointing to NULL\n", __func__, __LINE__);
        exit(1);
    }
    if(0 >= iLen){
        printf("[%s]:[%d] iLen less than or equal to 0\n", __func__, __LINE__);
        return 0;
    }
    if(1 == iLen){
        if(iMedian == iArr[0])
            return 1;
        return 0;
    }
    int numElement;         // number of elements
    int iter;               // trasverse array
    int index;              // trasverse sub array
    int midEle = 0, count=0, nearestMed=0;
    int result = 0;

    for(numElement=1; numElement < iLen+1; numElement++){
        for(iter=0; iter < iLen - numElement + 1; iter++){
            count = 0;
            nearestMed = 0;
            midEle = (numElement+1)/2;
            for(index=0; index < numElement; index++){
                printf("%d ", iArr[index+iter]);
                if(iArr[index+iter] <= iMedian){
                    count++;
                    if(iArr[index+iter] >= nearestMed){
                        nearestMed = iArr[index+iter];
                    }
                    // printf("\nIncrementing count!\n");
                }
            }
            // printf("\n\t\t\t\tCount = %d\t%d\tMed=%d", count, nearestMed, iMedian);
            if(iMedian == nearestMed && count<=midEle){
                result++;
                printf("\nIncrementing Result!");
            }
            printf("\n");
        }
    }
    printf("%d", result);
    
}