
int add(int num1, int num2, int * result);
int subtract(int num1, int num2, int * result);
int multiply(int num1, int num2, int * result);
int divide(int num1, int num2, int * result);
int modulo(int num1, int num2, int * result);

enum OPERATION {
  OPERATION_ADD,
  OPERATION_SUBSTRACT,
  OPERATION_MULTIPLY,
  OPERATION_DIVIDE,
  OPERATION_MODULO,
  OPERATION_MAX,
};

int doOperation(int operationType, int num1, int num2, int * result);
int getInput(int * operationType, int * num1, int * num2);

enum ERROR_CODES {
  SUCCESS,
  ERR_NULL_FOUND,
  ERR_DIVIDE_BY_ZERO,
  ERR_WRONG_DATATYPE,
  ERR_OUT_OF_BOUND,
};

