#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int combinationArray(const int iArr[], int iLen);
void printArr(const int iArr[], int iLen);
int min(int num1, int num2);
int comb(int iLen , int iter);


int main() {
    int arr[] = {1, 2, 3, 4};
    
    int result = combinationArray(arr, 4);
    return 0;
}

int combinationArray(const int iArr[], int iLen){
    
    // validating arguments
    if(NULL==iArr){
        printf("[%s]:[%d] iArr pointing to NULL\n", __func__, __LINE__);
        exit(1);
    }
    if(1>=iLen){
        printf("[%s]:[%d] iLen less than or equal to 1\n", __func__, __LINE__);
        return 0;
    }
    
    int twoArr[2][iLen];
    // memset(twoArr, -1, 2*iLen*sizeof(int));

    int pivot = 1, iter = 0;
    int index1 = 0, index2 = 0;
    int indexPivot = 0;
    
    for(index1 = 1; index1 < iLen; index1++){
        
        memset(twoArr, 0, 2*iLen*sizeof(int));
        // calculating index relative to pivot
        indexPivot = (index1 + pivot) % iLen;
        iter = min(pivot, iLen-pivot);

        /*
        4C2 = 4*3
        */

        iter = comb(iLen ,iter);
        printf("%d    ", iter);

        for(index2 = 0; index2 < pivot; index2++){
            twoArr[0][index2] = iArr[index2 + indexPivot];
        }
        for(index2 = pivot; index2 < iLen; index2++){
            twoArr[1][index2 - pivot] = iArr[index2 - pivot + indexPivot];
        }
        pivot++;
        printArr(twoArr[0], iLen);
        printArr(twoArr[1], iLen);
        printf("\n");
    }

}

void printArr(const int iArr[], int iLen){
    // validating arguments
    if(NULL == iArr){
        printf("[%s]:[%d] iArr pointing to NULL\n", __func__, __LINE__);
        return;
    }
    if(0 == iLen){
        printf("[%s]:[%d] iLen is equal to 0\n", __func__, __LINE__);
        return;
    }
    
    for(int index = 0; index < iLen; index++){
        printf("%d ", iArr[index]);
    }
    printf("\n");
}

int min(int num1, int num2){
    if(num1-num2>0)
        return num2;
    return num1;
}

int comb(int iLen , int iter)
{
    if (iter == 0 || iLen == iter)
    {
        return 1;
    }
    else
        return comb(iLen - 1, iter - 1) + comb(iLen - 1, iter);
}
/*
Definition-1
=============
You are given an array nums consisting of positive integers and an integer k.
Partition the array into two ordered groups such that each element is in exactly one group.
A partition is called great if the sum of elements of each group is greater than or equal to k.
Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.

Example 1:
Input: nums = [1,2,3,4], k = 4
Output: 6
Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).

Example 2:
Input: nums = [3,3,3], k = 4
Output: 0
Explanation: There are no great partitions for this array.

Example 3:
Input: nums = [6,6], k = 2
Output: 2
Explanation: We can either put nums[0] in the first partition or in the second partition.
The great partitions will be ([6], [6]) and ([6], [6]).
*/