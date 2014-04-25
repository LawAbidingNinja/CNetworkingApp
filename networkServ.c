#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <unistd.h>

//#include <sys/socket.h>

//int socket(int af, int type, int protocol);

int main (){
	
	const int PORT = 7000;
	
	printf("test %i, %i\n", AF_INET, SOCK_STREAM);
	
	//Create Socket
	int socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc==-1)
		perror("Create socket");
	printf("Socket Created, Descriptor: %i\n", socket_desc);
	
	//Bind Socket to port
	struct sockaddr_in address;
	
	/* type of socket created in socket() */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	/* 7000 is the port to use for connections */
	address.sin_port = htons(PORT);
	/* bind the socket to the port specified above */
	printf("Binding... 0 if ok: %i\n",bind(socket_desc,(struct sockaddr *)&address,sizeof(address)));
	
	
	//Listen for conns
	printf("Listening... 0 if ok: %i\n", listen(socket_desc,3));
	
	//Accept Conns
	
	int addrlen;
	int new_socket;
	
	addrlen = sizeof(address);
	new_socket = accept(socket_desc, (struct sockaddr *)&address, &addrlen);
	printf("Connection Recieved\n");
	if (new_socket<0)
		perror("Accept connection");
		
	 //Recieve Data
	 int bufsize =1024; ;        /* a 1K buffer */
	 char *buffer =malloc(bufsize);;
		
	 do{
		
		int bytes_recieved = recv(new_socket,buffer,bufsize,0);
		printf("Message: %s\nBytes Recieved %i\n", buffer, bytes_recieved);
		//printf("BUFFER[0] %c", buffer[0]);
     } while (buffer[0]!='0');
		
		
	 printf("Closing Socket... 0 if ok: %i\n", close(new_socket));
	 //To connect telnet localhost 7000

	return 0;
}
