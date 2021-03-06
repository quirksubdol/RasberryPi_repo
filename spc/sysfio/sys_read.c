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
	
	// File descriptor of file to read
	int fd;
	
	// Count of bytes read by read()
	ssize_t ct;
	
	// Buffer to store bytes read
	char buffer[BUFFER_SIZE];
	
	// Open the file for reading only
	fd = open("sys_read.c", O_RDONLY);
	
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return 1;
	}
	// Read up to BUFFER_SIZE bytes from the file into the buffer Lab: File I/O in C 4
	ct = read(fd, &buffer, BUFFER_SIZE);
 
	while(ct > 0) 							// While some bytes were read...
	{
		write(1, buffer, ct); 				// ...write the bytes to stdout
		ct = read(fd, &buffer, BUFFER_SIZE);// ..and read more bytes into the buffer
	}
	close(fd); 								// close the file
}
