# include <stdio.h>
# include <signal.h>

// signal handler function
void sighandler ( int signum ) 
{
	printf("SIGINT received. Inside sighandler\n") ;
}

int main(){
    signal( SIGINT, sighandler);
    while (1){
        printf("Program Running\n");
    }
    return 0 ;
}