#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define PORT 7000
 
int main(void)
{
  int listenfd = 0,connfd = 0;
  
  struct sockaddr_in serv_addr;
 
  char sendBuff[1025];  
  int numrv;  
 
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket Created\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
      
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(PORT);    
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
     
  
  /*while(1)
    {*/
    //Recieve Data
	 int bufsize =1024; ;        /* a 1K buffer */
	 char *buffer =malloc(bufsize);;
		
	 
      
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
  
      strcpy(sendBuff, "I am the Server, sending this message");
      write(connfd, sendBuff, strlen(sendBuff));
      //LAw start
      
      do{
		
		int bytes_recieved = recv(new_socket,buffer,bufsize,0);
		printf("Message: %s\nBytes Recieved %i\n", buffer, bytes_recieved);
		//printf("BUFFER[0] %c", buffer[0]);
     } while (buffer[0]!='0');
	//Law end
      close(connfd);    
      sleep(1);
    /*}*/
 
 
  return 0;
}
