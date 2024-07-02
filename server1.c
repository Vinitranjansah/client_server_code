#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>


int main(int argc,char *argv[]){

  char *ip =argv[1]; 
  int port = atoi(argv[2]);

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port =port; 
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");


    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");
while(1){
    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
	int i=strncmp(buffer,"bye",3);
  if(i==0)break;






printf("Client: %s", buffer);

    bzero(buffer, 1024);
   fgets(buffer,1024,stdin); 

    send(client_sock, buffer, strlen(buffer), 0);

	 i=strncmp(buffer,"bye",3);
  if(i==0)break;





}





printf(" client disconnected\n");
close(client_sock);
//printf(" client disconnected\n");
close(server_sock);
  return 0;
}
