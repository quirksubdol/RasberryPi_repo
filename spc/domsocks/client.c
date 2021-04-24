#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define server	"B00335350"
#define UNIX_PATH_MAX 	108

int main(void)
{
	struct sockaddr_un address;
	int  msg_socket;
	char buffer[1000], reply[2000];

	msg_socket = socket(PF_UNIX, SOCK_STREAM, 0);
	if(msg_socket < 0)
	{
		printf("socket() failed\n");
		return 1;
	}
		
	/* start with a clean address structure */
	//memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	snprintf(address.sun_path, UNIX_PATH_MAX, server);
	
	// connect to the server with error-handling
	if(connect(msg_socket, (struct sockaddr *) &address, sizeof(address)) != 0)
	{
		printf("connect() failed\n");
		return 1;
	}
	puts("Connected\n");
	
	//keep communicating with server
	while(1)
	{
		printf("Enter message : ");
		scanf("%s" , buffer);
		
		//Send some data
		if(send(msg_socket , buffer , strlen(buffer) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if(recv(msg_socket , reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		printf("Server reply:%s\n", reply);
		
	}
	

	close(msg_socket);

	return 0;
}
 
