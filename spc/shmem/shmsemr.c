#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>


key_t shared_key = 75013;
int shared_id;

struct shared_t {
     sem_t sem_wr_avail;
     sem_t sem_rd_avail;
     char shared_string[100];
};
struct shared_t *shared;
int shared_size = sizeof(struct shared_t);

int main(){
	
	shared_id = shmget(shared_key, shared_size, IPC_CREAT | 0666);
	shared = shmat(shared_id, NULL, 0);
	sem_init(&shared->sem_wr_avail, 1, 1);
	sem_init(&shared->sem_rd_avail, 1, 0);
	
	while (1)
	{
		sem_wait(&shared->sem_rd_avail);
		printf("%s\n", shared->shared_string);
		sem_post(&shared->sem_wr_avail);
		if (strcmp(shared->shared_string, "STOP") == 0)
		break;
	}
	
	sem_destroy(&shared->sem_wr_avail);
	sem_destroy(&shared->sem_rd_avail);
	shmdt(shared);
	shmctl(shared_id, IPC_RMID, NULL);
	return 0;
	
}
