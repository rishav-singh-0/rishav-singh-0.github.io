#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

ListNode *populateList(const int);
ListNode *addTwoNumbers(ListNode *, ListNode *);
int lenList(const ListNode *);
void printList(const ListNode *);
void freeList(ListNode *);

int main() {
    ListNode* Num1 = populateList(12342);
    ListNode* Num2 = populateList(465);

    ListNode* result = addTwoNumbers(Num1, Num2);
    printList(result);
    freeList(Num1); Num1 = NULL;
    freeList(Num2); Num2 = NULL;
    freeList(result); result = NULL;

    return 0;
}

ListNode* populateList(int iNum){
    int rem = iNum%10;
    iNum = iNum/10;

    ListNode* newListPtr = (ListNode*)malloc(sizeof(ListNode));
    newListPtr->data = rem;
    if(iNum!=0){
        newListPtr->next = populateList(iNum);
        return newListPtr;
    }
    newListPtr->next = NULL;
    return newListPtr;
}

int lenList(const ListNode* iHead){
    int len = 0;
    const ListNode* ptr = iHead;
    for(len=0; NULL!=ptr; ptr=ptr->next, len++);
    // printf("%d\n", len);
    return len;
}

void freeList(ListNode* iHead){
    ListNode* tmp;

    while (iHead != NULL){
        tmp = iHead;
        iHead = iHead->next;
        free(tmp);
    }
}

void printList(const ListNode* iHead){
    while ( NULL != iHead){
        printf("%d ->", iHead->data);
        iHead = iHead->next;
    }
    printf("NULL\n");
}

ListNode * addTwoNumbers(ListNode* iList1_Ptr, ListNode* iList2_Ptr){

    if( NULL ==iList1_Ptr){
        printf("[%s]:[%d] iList1_Ptr of Link List is pointing to NULL\n", __func__, 75);
        return NULL;
    }
    if( NULL ==iList2_Ptr){
        printf("[%s]:[%d] iList2_Ptr of Link List is pointing to NULL\n", __func__, 79);
        return NULL;
    }

    ListNode* newListPtr = (ListNode*)malloc(sizeof(ListNode));
    ListNode* result = newListPtr;
    int listLen1 = lenList(iList1_Ptr);
    int listLen2 = lenList(iList2_Ptr);

    int addition, carry = 0;
    int iter = listLen1;
    if(listLen2>iter){
        iter = listLen2;
    }

    int num1 = iList1_Ptr->data, num2 = iList2_Ptr->data;
    while(0!=iter){
        iter--;

        addition = carry + num1 + num2;
        carry = addition/10;
        addition = addition%10;
        // printf("%d, %d\n", carry, addition);
        result->data = addition;

        if(iter){
            result->next = (ListNode*)malloc(sizeof(ListNode));
            result = result->next;
        }

        if(NULL != iList1_Ptr->next){
            iList1_Ptr = iList1_Ptr->next;
            num1 = iList1_Ptr->data;
        }
        else{ num1 = 0;}

        if(NULL != iList2_Ptr->next){
            iList2_Ptr = iList2_Ptr->next;
            num2 = iList2_Ptr->data;
        }
        else{ num2 = 0;}
    }
    free(result->next);
    result = NULL;

    return newListPtr;
}
