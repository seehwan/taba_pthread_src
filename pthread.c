       #include <pthread.h>
       #include <string.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <errno.h>
       #include <ctype.h>

long long balance = 0;
pthread_mutex_t lock;

static void * deposit(void *arg)
{
	int *uargv = malloc(sizeof(int));
	int num = *(int *)arg;
	printf("deposit: num: %d\n", num);
	for (int i = 0 ; i < num; i++) {
		pthread_mutex_lock(&lock);
		for (int j = 0 ; j < 0x1000 ; j++)
			balance += i;
		pthread_mutex_unlock(&lock);
	}
	return uargv;
}

static void * withdraw(void *arg)
{
	int *uargv = malloc(sizeof(int));
	int num = *(int *)arg;
	printf("withdraw: num: %d\n", num);
	pthread_mutex_lock(&lock);
	for (int i = 0 ; i < num; i++) {
		for (int j = 0 ; j < 0x1000 ; j++)
			balance -= i;
	}
	pthread_mutex_unlock(&lock);

	return uargv;
}

int
main(int argc, char *argv[])
{
	pthread_t tid1, tid2;
	void *res;
	int num  = 0x100000;
	int num2 = 0x100000;
	printf("balance: %lld \n", balance);


	pthread_mutex_init(&lock, NULL);
	pthread_create(&tid1, NULL, &deposit, &num);
	pthread_create(&tid2, NULL, &withdraw, &num2);

	pthread_join(tid1, &res);
	free(res);
	pthread_join(tid2, &res);
	free(res);

	printf("balance: %lld \n", balance);

	exit(0);
}
