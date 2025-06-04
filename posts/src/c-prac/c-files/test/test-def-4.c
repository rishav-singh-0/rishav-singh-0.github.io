#include <stdio.h>
#include <math.h>

#define OPERATE(x) {x*iNum, x/iNum, x+iNum, x-iNum}
#define DIFF(arr, x) {x-arr[0], x-arr[1], x-arr[2], x-arr[3]}

enum OPERATOR{MUL, DIV, ADD, SUB};
char* gSign[] = {" * ", " / ", " + ", " - "};

int operatorCounter(const int iTarget, const int iNum, int diff);
void printArr(int* arrPtr);

int main() {
    int target = 19;
    int num = 3;
    int numOperator;

    numOperator = operatorCounter(target, num, num);
    printf("Number of operators used: %d\n", numOperator);
    return 0;
}

int operatorCounter(const int iTarget, const int iNum, int iPrev){
    
    // if(iTarget==iNum){
    //     printf(" %d", iNum);
    //     return 0;
    // }

    int operators = 1;
    int operations[4] = OPERATE(iNum);
    printArr(operations);
    int diffAll[4] = DIFF(operations, iTarget);

    int minDiff = fabs(diffAll[0]);
    int tDiff, nearestOper=0;
    printf("%d\t", diffAll[0]);
    for(int index=1; index<4; index++){
        tDiff = fabs(diffAll[index]);
        printf("%d\t", tDiff);
        if(tDiff < minDiff){
            minDiff = tDiff;
            nearestOper = index;
        }
    }
    
    printf("MinDiff = %d\n", minDiff);
    
    if(minDiff > 1){
        operators += operatorCounter(minDiff, iNum, operations[nearestOper]);
    }
    else{
        printf("%d", iNum);
        return 1;
    }
    
    printf("%s %d",gSign[nearestOper], iNum);
    return operators;
}

void printArr(int *arrPtr){
    for(int i=0; i<4; i++){
        printf("%d ", arrPtr[i]);
    }
    printf("\n");
}