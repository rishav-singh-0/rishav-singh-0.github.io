#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {false, true} bool;

bool strMatch(const char * iStrPtr, int iStrLen, const char *iPatPtr, int iPatLen);

int main() {
    
    char str[] = "aa";
    char pattern[] = "baa";
    bool result;

    result = strMatch(str, strlen(str), pattern, strlen(pattern));
    if(result){
        printf("true\n");
    }
    else{
        printf("false\n");
    }
    
    return 0;
}

bool strMatch(const char * iStrPtr, int iStrLen, const char *iPatPtr, int iPatLen){
    // arguments validation
    if(NULL == iStrPtr){
        fprintf(stderr, "[%s]:[%d] iStrPtr pointing to NULL\n", __func__, __LINE__);
        exit(0);
    }
    if(0 >= iStrLen){
        fprintf(stderr, "[%s]:[%d] Invalid iStrLen\n", __func__, __LINE__);
        exit(0);
    }
    if(NULL == iPatPtr){
        fprintf(stderr, "[%s]:[%d] iPatPtr pointing to NULL\n", __func__, __LINE__);
        exit(0);
    }
    if(0 >= iPatLen){
        fprintf(stderr, "[%s]:[%d] Invalid iStrLen\n", __func__, __LINE__);
        exit(0);
    }
    
    // '.' Matches any single character.
    // '*' Matches zero or more of the preceding element.
    
    int maxLen = iStrLen;
    if(iPatLen < iStrLen){
        maxLen = iPatLen;
    }

    bool result = true;
    int index1 = 0, index2;
    char prevChar = iStrPtr[0];
    while(index1<iStrLen){
        // printf("Comparing: %c, %c\n", iStrPtr[index1], iPatPtr[index2]);
        if(iPatPtr[index2] == '*' && prevChar == '*'){
            index2++;
        }
        if(iStrPtr[index1] == iPatPtr[index2]){
            index1++; index2++;
        }
        else if(prevChar == '*'){
            index1++;
        }
        else if (iPatPtr[index2] == '*')
        {
            prevChar = iPatPtr[index2];
            index1++; index2++;
        }
        else if (iPatPtr[index2] == '.')
        {
            index1++; index2++;
        }
        else{
            return false;
        }
        
        // prevChar = iStrPtr[index1];
    }

    return result;
}