#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t mypid, cpid;
	int i;

	cpid = fork();
	 if (cpid > 0) {
		 // parent
	    mypid = getpid();
	    printf("[%d] parent of [%d]\n", mypid, cpid);
	    for (i=0; i<100; i++) {
			printf("[%d] parent: %d\n", mypid, i);
			sleep(1);
		}
	}  else if (cpid == 0) {
		// child
		mypid = getpid();
		printf("[%d] child\n", mypid);
		for (i=0; i>-100; i--) {
			printf("[%d] child: %d\n", mypid, i);
			sleep(1);                             
		}
	} 

	return 0;
}

