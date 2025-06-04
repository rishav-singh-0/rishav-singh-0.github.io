#include <stdio.h>

void move ( int n, char sp, char ap, char ep )
{
	// Write your code here
    
    if (n==1){
        printf( "Move from %c to %c\n", sp, ep );
    }
    else{
        move(n-1, sp, ep, ap);
        move(1, sp, ' ', ep);
        move(n-1, ap, sp, ep);
    }
    
} 

int main(){
    move(3 , 'A' , 'B' , 'C');
    return 0;
}

// 2
// Move from A to B
// Move from A to C
// Move from B to C

// 3
// Move from A to C
// Move from A to B
// Move from C to B
// Move from A to C
// Move from B to A
// Move from B to C
// Move from A to C

// 4
// Move from A to B
// Move from A to C
// Move from B to C
// Move from A to B
// Move from C to A
// Move from C to B
// Move from A to B
// Move from A to C
// Move from B to C
// Move from B to A
// Move from C to A
// Move from B to C
// Move from A to B
// Move from A to C
// Move from B to C

// 5
// Move from A to C
// Move from A to B
// Move from C to B
// Move from A to C
// Move from B to A
// Move from B to C
// Move from A to C
// Move from A to B
// Move from C to B
// Move from C to A
// Move from B to A
// Move from C to B
// Move from A to C
// Move from A to B
// Move from C to B
// Move from A to C
// Move from B to A
// Move from B to C
// Move from A to C
// Move from B to A
// Move from C to B
// Move from C to A
// Move from B to A
// Move from B to C
// Move from A to C
// Move from A to B
// Move from C to B
// Move from A to C
// Move from B to A
// Move from B to C
// Move from A to C