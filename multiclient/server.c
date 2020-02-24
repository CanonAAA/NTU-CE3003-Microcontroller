
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>


char client_message[2000];
char buffer[1024];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg) 
{
    int newSocket = *((int *) arg);
    recv(newSocket, client_message, 2000,0);
    pthread_mutex_lock(&lock);
    char *msg = malloc(sizeof(client_message)+20);
    strcpy(msg, "Hello Client: ");
    strcat(msg, client_message);
    strcpy(msg,"\n");
    strcpy(buffer,msg);
    free(msg);

    pthread_mutex_unlock(&lock);
    send(newSocket,buffer,13,0);
    printf("Exit socketThread\n");
    close(newSocket);
    pthread_exit(NULL); 
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 


    struct sockaddr_in address; 

    struct sockaddr_storage serverStorage;
    socklen_t addr_size; 

    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 


    //char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    int PORT = atoi(argv[1]);
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    

    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if(listen(server_fd,4)==0)

        printf("Listening\n");

     else

    printf("Error\n");

    pthread_t tid[4];

    int i = 0;

    while(1)

    {
//Accept call creates a new socket for the incoming connection

        addr_size = sizeof serverStorage;

        new_socket = accept(server_fd, (struct sockaddr *) &serverStorage, &addr_size);

        //for each client request creates a thread and assign the client request to it to process

       //so the main thread can entertain next request

        if( pthread_create(&tid[i], NULL, socketThread, &new_socket) != 0 )

           printf("Failed to create thread\n");

        if( i >= 4)

        {

          i = 0;

          while(i < 4)

          {

            pthread_join(tid[i++],NULL);

          }

          i = 0;

        }

    }

  return 0;

} 



