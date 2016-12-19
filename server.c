#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


#include "doprocessing.h"


int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, port, clilent;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
 
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   port = 9999;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   
  

   printf("Welcome to this server, my process id is %d\n", getpid());

   listen(sockfd,5);
   clilent = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,(socklen_t *)  &clilent);
		
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      
      pid = fork();
		
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         
         close(sockfd);
         printf("New connection, my process id is %d\n", getpid());
         doprocessing(newsockfd);
         exit(0);
      }
      else {
         close(newsockfd);
      }
		
   } 
}
