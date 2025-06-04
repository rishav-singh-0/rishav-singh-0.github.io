#include <stdio.h>
#include <errno.h>

int fun() {
    FILE * f1;
    int num=0;
    int randomHex=0x15c;
    f1 = fopen("text_file.txt", "r");
    if(f1==NULL){
        f1 = fopen("text_file.txt", "w");
        num = 1;
        fprintf(f1, "%d\n", num);
        fprintf(f1, "%x\n", randomHex);
    }
    else{
        fscanf(f1, "%d", &num);
        fscanf(f1, "%x", &randomHex);
        printf("Random Num: %x\n", randomHex);
        fclose(f1);
        if(num>9){
            remove("text_file.txt");
            printf("Last Num: %d\n", num);
            return 0;
        }

        f1 = fopen("text_file.txt", "r+");
        num++;
        printf("Num: %d\n", num);
        fprintf(f1, "%d\n", num);
        fprintf(f1, "%x\n", randomHex);

    }
    // printf("Ptr Location: %ld\n", ftell(f1));
    fclose(f1);
    // remove("text_file.txt");

    return 0;
}

int main(){
    fun();
}