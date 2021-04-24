#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

key_t shared_key = 14724;
int shared_id;
char *shared_string, msg[50], sp_ch[] = "@";
char message[100];
size_t shared_size = 100;


int main()
{
	shared_id = shmget(shared_key, shared_size, 0666);
	
	if (shared_id == -1) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	printf("Attached to process: %d\nPress enter to continue", shared_id);
	getchar();
	// key press check allows us to check the 2 attachments to the shared memory segment
	
	shared_string = shmat(shared_id, NULL, 0);
	
	if (shared_string == (void *) -1) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	
	
	shared_string = message;
	if(message[0] != '@'){
		printf("Message form the first process:%s", message);
		getchar();
		printf("\nInput message: ");
		scanf("%s", msg);
		shared_string = strcat(sp_ch, msg);
		printf("message to be sent:%s", shared_string);
		getchar();
	}else{
		
	}
	
	// wait for key press so we can use ipcs in the command line
	getchar();
	
	if (shmdt(shared_string) == -1) {
		perror("shmdt");
		exit(EXIT_FAILURE);
	}
	
	printf("Detached from shared memory\n");
	// getchar();
	// shmctl(shared_id, IPC_RMID, NULL);
	// printf("Shared memory marked for removal\n");
	return 0;
}
