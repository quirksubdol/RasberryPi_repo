#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define FIFO_NAME "myfifo"

int main()
{
	char buf[100];
	int fd, count = 0;
	int bytes_read;
	char message[100];
	
	// Create the FIFO if it doesn’t exist
	if (mkfifo(FIFO_NAME, 0644) == -1) {
		if (errno != EEXIST) {
			perror("mkfifo");
			exit(1);
		}
	}
	
	// Open this end of the FIFO for reading
	if ((fd = open(FIFO_NAME, O_RDONLY)) == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	// reading 5 messages from the FIFO file
	// TASK 2
	while(count < 6){
		// Read from the FIFO
		if ((bytes_read = read(fd, buf, 100)) == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		// append the new message to the array
		strcat(message, buf);
		count++;
		
	}
	
	
	printf("Bytes received: %d\n", bytes_read);
	printf("Messages received: %s\n", message);
	
	// Close the FIFO
	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
