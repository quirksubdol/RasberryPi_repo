#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

key_t shared_key = 14724;
int shared_id;
char *shared_string;
size_t shared_size = 100;
char ans[50];


int main()
{
	shared_id = shmget(shared_key, shared_size, IPC_CREAT | 0666);
	
	if (shared_id == -1) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	printf("Shared memory created and attached...press RETURN\n");
	getchar();
	
	shared_string = shmat(shared_id, NULL, 0);
	
	if (shared_string == (void *) -1) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	// task 1 second part of the lab (try for a sync function)
	shared_string = ans;
	if(ans[0] != '@'){
	// Exercise 4 task for user input
		printf("Input your test message: ");
		scanf("%s", ans);
		sprintf(shared_string, ans);
		getchar();
		getchar();
	}else{
		printf("message:%s", shared_string);
		getchar();
	}
	
	if (shmdt(shared_string) == -1) {
		perror("shmdt");
		exit(EXIT_FAILURE);
	}
	
	printf("Shared memory detached...press RETURN\n");
	getchar();
	shmctl(shared_id, IPC_RMID, NULL);
	printf("Shared memory marked for removal\n");
	return 0;
}
