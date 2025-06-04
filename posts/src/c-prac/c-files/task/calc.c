#include<stdio.h>
#include "calc_prototypes.h"

int add(int num1, int num2, int * result){
  
  // validating arguments
  if(NULL==result){
    printf("[%s]:[%d] Result pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  *result = num1 + num2;
  return SUCCESS;
}

int subtract(int num1, int num2, int * result){
  
  // validating arguments
  if(NULL==result){
    printf("[%s]:[%d] Result pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  *result = num1 - num2;
  return SUCCESS;
}

int multiply(int num1, int num2, int * result){
  
  // validating arguments
  if(NULL==result){
    printf("[%s]:[%d] Result pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  *result = num1 * num2;
  return SUCCESS;
}

int divide(int num1, int num2, int * result){
  
  // validating arguments
  if(NULL==result){
    printf("[%s]:[%d] Result pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }
  
  if(0==num2){
    printf("[%s]:[%d] Trying to divide by 0\n", __func__, __LINE__);
    return ERR_DIVIDE_BY_ZERO;
  }

  //Missing 0 validation of num2 -> leads to crash
  *result = num1 / num2;
  return SUCCESS;
}

int modulo(int num1, int num2, int * result){
  
  // validating arguments
  if(NULL==result){
    printf("[%s]:[%d] Result pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  if(0==num2){
    printf("[%s]:[%d] Trying to divide by 0\n", __func__, __LINE__);
    return ERR_DIVIDE_BY_ZERO;
  }

  //Missing 0 validation of num2 -> leads to crash
  *result = num1 % num2;
  return SUCCESS;
}

int (*gOperation[OPERATION_MAX])(int, int, int *) = {add, subtract, multiply, divide, modulo};

int doOperation(int operationType, int num1, int num2, int * result){

  // validating arguments
  if(operationType < OPERATION_ADD){
    printf("[%s]:[%d] operation type is less than 0\n", __func__, __LINE__);
    return ERR_OUT_OF_BOUND;
  }

  if(operationType >= OPERATION_MAX){
    printf("[%s]:[%d] operation type is more than %d\n", __func__, __LINE__, OPERATION_MAX);
    return ERR_OUT_OF_BOUND;
  }

  int error_type = (*gOperation[operationType])(num1, num2, result);

  // printf("%d, %d", *result, error_type);

  return error_type;
}

int getInput(int * operationType, int * num1, int * num2){

  // Input validation
  if(NULL==operationType){
    printf("[%s]:[%d] Invalid operationType, NULL found\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  if(NULL==num1){
    printf("[%s]:[%d] Num 1 pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  if(NULL==num2){
    printf("[%s]:[%d] Num 2 pointing to NULL\n", __func__, __LINE__);
    return ERR_NULL_FOUND;
  }

  printf("Enter operation type:\n");
  printf("0: ADD\n1: SUB\n2: MUL\n3: DIV\n4: MODULO\n");
  scanf("%d", operationType);

  printf("Enter two intergers:\n");
  if (scanf("%d %d", num1, num2) !=2){
    printf("[%s]:[%d] Invalid Integers\n", __func__, __LINE__);
  }

  return SUCCESS;
}

int main(){
  int num1, num2, result;
  // enum OPERATION operationType;
  int operationType;

  // getInput();
  int inputErrValue = getInput(&operationType, &num1, &num2);

  // do not move forward if exit code is not 0
  if(inputErrValue){
    return inputErrValue;
  }

  int operationErrValue = doOperation(operationType, num1, num2, &result);

  printf("%d\t%d\t%d\n", num1, num2, result);

  return operationErrValue;
}

