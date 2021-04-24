#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define server	"B00335350"
#define UNIX_PATH_MAX 	108


int main(){
	
	int listen_soc, message_soc;
	char buffer[1000];
	int nbytes;
	
	struct sockaddr_un address;	
	socklen_t address_length;
	
	listen_soc = socket(AF_UNIX, SOCK_STREAM, 0);
	if(listen_soc < 0)
	{
		printf("socket() failed\n");
		return 1;
	}
	
	//Set the attributes of the address struct
	address.sun_family = AF_UNIX;
	snprintf(address.sun_path, UNIX_PATH_MAX, server);
	unlink(server);
	
	if(bind(listen_soc, (struct sockaddr *) &address, sizeof(struct sockaddr_un)) < 0)
	{
		printf("bind() failed\n");
		return 1;
	}
	
	if(listen(listen_soc, 3) != 0)
	{
		printf("listen() failed\n");
		return 1;
	}
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	address_length = sizeof(address);
	
	//accept connection from an incoming client
	message_soc = accept(listen_soc, (struct sockaddr *) &address, &address_length);
	
	if(message_soc < 0)\
	{
			printf("accept() failed\n");
			return 1;
	}
	puts("Connection accepted");
	
	while((nbytes = recv(message_soc , buffer , 1000 , 0)) > 0 )
	{
		//display the message
		printf("Client message:%s\n", buffer);
		//Send the message back to client
		write(message_soc , buffer , strlen(buffer));
		//clear the buffer for new message
		for(int i=0; i <= 1000; i++)
		{
			buffer[i] = 0;
		}
	}
	
	if(nbytes == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(nbytes == -1)
	{
		perror("recv failed");
	}
	
		
	close(listen_soc);
	close(message_soc);
	unlink(server);
	
}
