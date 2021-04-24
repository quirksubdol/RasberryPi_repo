#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


int main()
{
	unsigned int priority;
	mqd_t mqd;
	char buf[8192];
	
	if ((mqd = mq_open("/mq1", O_RDONLY)) == -1) {
		perror ("mq_open");
		exit(EXIT_FAILURE);
	}
	
	while (1){
		
		if (mq_receive(mqd, buf, 8192, &priority) == -1) {
			perror ("mq_receive");
			exit(EXIT_FAILURE);
		}
		
		// Stop the receiver if '.' is entered
		if (buf[0] == '.'){
			break;
		}
		
		printf ("%s, %d\n", buf, priority);
	}
	
	// printf ("%s\n", buf);
	if (mq_close(mqd) == -1) {
		perror ("close");
		exit(EXIT_FAILURE);
	}
	return 0;
}
