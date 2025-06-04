# include <stdio.h>
# include <unistd.h>
# include <signal.h>

// First signal handler
void  f1 ( int signum ) 
{
		printf ( "\nSIGINT Recd" ) ;
}
// Second signal handler
void  f2 ( int signum ) 
{
		printf ( "\nSIGTERM Recd.\n" ) ;
}
int main( ) 
{	
		signal ( SIGINT, f1 ) ;	
		signal ( SIGTERM, f2 ) ;
			
		while ( 1 ) {
			// printf ( "\nRunning" ) ;
        }
	
		return 0 ;
}

// to kill this process:
// kill -SIGKILL pid