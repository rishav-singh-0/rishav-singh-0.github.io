#include <stdio.h>
#include <math.h>
void papersizes ( int, int, int, int ) ;

int main( )
{
	papersizes ( 0, 7, 1189, 841 );
}

void papersizes ( int i, int n, int l, int b )
{
	// Write your code here
	printf ( "A%d:L = %d B = %d\n", i, l, b );
	if (n>0){
        // printf("%f\n", 1.0*l/b);
		papersizes(i+1, n-1, b, l/2);
	}
	// printf("\n");

}


// A0:L = 1189 B = 841\n
// A1:L = 841 B = 594\n
// A2:L = 594 B = 420\n
// A3:L = 420 B = 297\n
// A4:L = 297 B = 210\n
// A5:L = 210 B = 148\n
// A6:L = 148 B = 105\n
