#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main()
{
	char buf[100];
	int fd;
	
	// Create the FIFO if it doesn’t exist
	if (mkfifo(FIFO_NAME, 0644) == -1) {
		if (errno != EEXIST) {
			perror("mkfifo");
			exit(1);
			}
	}
	
	// Open this end of the FIFO for writing
	if ((fd = open(FIFO_NAME, O_WRONLY | O_APPEND)) == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		// Send a string from the user (TASK 1) to the FIFO
		printf("Message: ");
		fgets(buf, 100, stdin);
		if (write(fd, buf, strlen(buf)+1) == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
	
	// Close the FIFO
	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
	return 0;
}
