//client code

#include<stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>



int main(int argc,char* argv[]){

  char *ip = argv[1];
  int port = atoi(argv[2]);

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;
 
 //int sockfd = socket(domain, type, protocol)
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;    
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
while(1){
  bzero(buffer, 1024);
fgets(buffer,1024,stdin);

  send(sock, buffer, strlen(buffer), 0);

int i=strncmp(buffer,"bye",3);
  if(i==0)break;


  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Server: %s", buffer);
  i=strncmp(buffer,"bye",3);
  if(i==0)break;
}
  close(sock);
  printf("Disconnected from the server.\n");

  return 0;

}
