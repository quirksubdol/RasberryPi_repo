/*
 Use the system calls open(), read(), write() and close()
 to open, read, display and close a text file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main() {
	
	int fd; 					// File descriptor of file to read
	ssize_t ct; 				// Count of bytes read by read()
	char buffer[BUFFER_SIZE]; 	// Buffer to store bytes read
	
	fd = open("sys_read.c", O_RDONLY); 		// Open the file for reading only
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return 1;
	}
	
	ct = read(fd, &buffer, BUFFER_SIZE); 	// Read up to BUFFER_SIZE bytes from the file into the buffer Lab: File I/O in C 4
 
	while(ct > 0) 							// While some bytes were read...
	{
		write(1, buffer, ct); 				// ...write the bytes to stdout
		ct = read(fd, &buffer, BUFFER_SIZE);// ..and read more bytes into the buffer
	}
	close(fd); 								// close the file
}
