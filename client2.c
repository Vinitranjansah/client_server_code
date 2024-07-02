#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc,char* argv[]){

  char *ip = argv[1];
  int port = atoi(argv[2]);

  int sock;
  struct sockaddr_in addr;
//  socklen_t addr_size;
  char buffer[1024];
  int n;

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
  
  //int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
    pid_t pid =fork();
    
    if(pid!=0){
        //parent process of client side
        
        while(1){
            bzero(buffer,1024);
            fgets(buffer,1024,stdin);
            send(sock, buffer, strlen(buffer), 0);
            int   i=strncmp(buffer,"bye",3);
                if(i==0){
                printf("close parent\n");
                close(sock);
                
                kill(pid,SIGINT);
                exit(0);
                     }

        }
    }
    else{
        //child process of client side
        
        while(1){
            bzero(buffer, 1024);
            if(recv(sock, buffer, sizeof(buffer), 0)<0){
                perror("[-]receive error");
                break;
            }
            int i=strncmp(buffer,"bye",3);
            printf("server: %s", buffer);
            if(i==0){
                printf("close child\n");
                close(sock);
               
                kill(pid,SIGINT);
                exit(0);
            }

        }
    }
  return 0;

}
              
