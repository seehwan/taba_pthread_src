#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include <unistd.h>
#include <signal.h>

int count = 0;
void signal_callback_handler(int signum)
{
	printf("Caught signal %d - phew! %d\n",signum, count);
	count++;
//	exit(1);
}

int main() {
	signal(SIGINT, signal_callback_handler);

	while (1) {}
}


