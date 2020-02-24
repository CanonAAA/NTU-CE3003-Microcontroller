#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void * clientThread(void *arg) 
{
	long tid;
        tid = (long) arg;
	printf("Thread %ld executing.\n",tid);
	char msg[1000];
	char buffer[1024];
	int client_socket;
	struct sockaddr_in server_address;
	socklen_t addr_size;
	
	  // Create the socket. 

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;

	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = inet_addr("localhost");
	memset(server_address.sin_zero, '\0', sizeof server_address.sin_zero);
	addr_size = sizeof(server_address);
	connect(client_socket, (struct sockaddr *) &server_address, addr_size);
        pthread_mutex_lock(&lock);
	printf("Print your message to server: \n");
	fgets(msg, sizeof(msg),stdin);
	printf("Preparing message [%s]to send to server\n",msg);
   	if( send(client_socket , msg , strlen(msg) , 0) < 0)

	    {

		    printf("Send failed\n");

	    }

	    //Read the message from the server into the buffer
	printf("Receiving the message from server.\n");
	    if(recv(client_socket, buffer, 1024, 0) < 0)

	    {

	       printf("Receive failed\n");

	    }

    //Print the received message

    printf("Data received: %s\n",buffer);
    pthread_mutex_unlock(&lock);
    close(client_socket);
     
    pthread_exit(NULL);
}
int main(){

  int i = 0;

  pthread_t tid[4];

  while(i< 4)

  {

    if( pthread_create(&tid[i], NULL, clientThread, (void *)i) != 0 )

           printf("Failed to create thread\n");

    i++;
printf("Thread %d created.\n",i);

  }

  sleep(20);

  i = 0;

  while(i< 4)

  {
     printf("Thread %d exiting.\n",i);	
     pthread_join(tid[i++],NULL);

     printf("%d:\n",i);

  }

  return 0;

}
/*
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    int port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    char hello[1024];
    printf("Enter the message: ");
    fgets(hello,sizeof(hello),stdin);
    //printf("This is the string to send: %s - I have no idea\n",hello); 		
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 
*/
