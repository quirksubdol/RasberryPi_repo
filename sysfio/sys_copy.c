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
	
	int fd, fd2; 				// File descriptor of file to read
	ssize_t ct; 				// Count of bytes read by read()
	char buffer[BUFFER_SIZE]; 	// Buffer to store bytes read
	
	fd2 = open("f_out.txt", O_CREAT);		// Creates the file to copy 
	
	fd = open("sys_read.c", O_RDONLY); 		// Open the file for reading only
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return 1;
	}
	
	ct = read(fd, &buffer, BUFFER_SIZE); 	// Read up to BUFFER_SIZE bytes from the file into the buffer Lab: File I/O in C 4
	fd2 = open("f_out.txt", O_WRONLY);
	
	while(ct > 0) 							// While some bytes were read...
	{
		write(fd2, buffer, ct); 			// ...write the bytes to the second file f_out.txt
		ct = read(fd, &buffer, BUFFER_SIZE);// ..and read more bytes into the buffer
	}
	close(fd); 								// close the file
	close(fd2);
}
