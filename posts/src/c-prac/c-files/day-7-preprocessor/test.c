#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Driver Code
int main()
{
	int sec;
	time_t time1, time2;

	// Current time
	time(&time1);
	// for (sec = 1; sec <= 6; sec++)
	// 	sleep(1);

	// time after sleep in loop.
	time(&time2);
	printf("Difference is %.2f seconds",
		difftime(time2, time1));

	return 0;
}