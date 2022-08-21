#include <pthread.h>
#include <stdio.h>

void* thread_test(void* ptr)
{
	while(1)
        printf("i am pthread\n");
}
int main()
{
    int i = 10;
	pthread_t pid;
	pthread_create(&pid, NULL, thread_test, NULL);
    while(i--)
		printf("i am main pthread\n");
	return 0;
}
