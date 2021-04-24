#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <stdbool.h>

key_t shared_key = 75013;
int shared_id;

struct shared_t {
	sem_t sem_safe_to_write;
	sem_t sem_safe_to_read;
	char shared_string[100];
};
struct shared_t *shared;
int shared_size = sizeof(struct shared_t);

int main()
{
	char message[100];
	bool stop = false;
	
	shared_id = shmget(shared_key, shared_size, 0666);
	shared = shmat(shared_id, NULL, 0);
	
	
	while(!stop){
		
		sem_wait(&shared->sem_safe_to_write);
		
		printf("Input message: ");
		scanf("%s", message);
		
		/*
		 * For now there is a bug in the input message checking method
		 * which makes the reader process split the string if there are
		 * spaces in the input message and displays the message line by line
		 * */
		
		// process is set as ready to read the message
		sem_post(&shared->sem_safe_to_read);
		
		// case where input is empty
		if (message == NULL){
			sprintf(shared->shared_string, "<no input>");
		}
		// if the message matches with "STOP" string
		if(strcmp(message, "STOP") == 0){
			sprintf(shared->shared_string, message);
			stop = true;
		}
		// if input is valid, the message is stored in the shared_string
		else{
			sprintf(shared->shared_string, message);
		}
		
	}
	
	shmdt(shared);
	
	return 0;
}
