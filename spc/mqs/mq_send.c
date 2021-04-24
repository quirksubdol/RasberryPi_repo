#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>


int main()
{
	int priority[5] = {2, 1, 1, 4, 3};
	mqd_t mqd;
	char user_buf[100];
	int i = 0;
	
	if ((mqd = mq_open("/mq1", O_WRONLY | O_CREAT, 0644, NULL)) == -1){
		perror ("open");
		exit(EXIT_FAILURE);
	}
	
	// Sender sends messages to the queue
	while (fgets(user_buf, 100, stdin) != NULL){
		
		// Every 5 messages, the same cycle of priority applies
		// and resets afterwards
		if(i == 5){
			i = 0;
		}
		
		// Send the message to the queue 
		if (mq_send(mqd, user_buf, strlen(user_buf) + 1, priority[i]) == -1) {
			perror ("mq_send");
			}
		
		// move to the next priority value
		i++;
		
	}
	
	
	if (mq_close(mqd) == -1) {
		perror ("close");
		exit(EXIT_FAILURE);
	}
	
	if (mq_unlink("/mq1") == -1) {
		perror ("unlink");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
