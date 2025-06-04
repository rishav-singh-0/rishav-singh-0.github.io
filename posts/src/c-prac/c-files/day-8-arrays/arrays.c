#include<stdio.h>

int main(){
    // int a[3]={1, 2, 3, 4};
    
    // for(int i=0; i<3; i++){
    //     printf("%d", a[i]);
    // }
    
	char *s = "geeksquiz";
	// s[0] = 'j'; // segmentation fault
	printf("%lu %s", sizeof(s), s); // size = 8
    printf("\n%lu %lu", sizeof(int *), sizeof(size_t));
    
   char str[20] = {'a', "b", 'c', "a", 'e', "f", "g", "h"};
//    gets(str);
    for(int i=0; i<sizeof(str); i++){
        printf("%d:\t%c\t%d\n", i, str[i], str[i]);
    }
//    printf("\n%s", str);

}