#include <stdio.h>

int main() {
    int a = 6;

    switch (a){
        case 5 ...5:
            printf("First case");
            break;
        default:
            printf("Default");
            break;
    }
    
    for(int i=0; i<3; i++){
        for(int k=0; k<3; k++){
            printf("\n%d %d", i, k);
            if(i==0)
                continue;
            if(k==1)
                break;
        }
    }

    return 0;
}