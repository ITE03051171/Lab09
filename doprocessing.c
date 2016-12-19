#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


void doprocessing (int sock) 
{
   int n;
   char buffer[256];

   
	 
	int answer[8];
	int c1,c2,a,b;
	char *message;
	char reply[8],compare[8],message2[50];
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
	a=0; 
	b=0;
	srand( time(NULL) ); 
	for(c1=0;c1<4;c1++)
	{
		answer[c1]=rand()%10; 
		for(c2=0;c2<c1;c2++) 
		{ 
			if(answer[c1]==answer[c2]) 
			{
			c1--; 
			} 
		}
	} 
	printf("Answer:%d%d%d%d\n",answer[0],answer[1],answer[2],answer[3]);

	while(1)
	{
		bzero(buffer,256);
		n = read(sock,buffer,255);
		compare[0]=(buffer[0]-'0');
		compare[1]=(buffer[1]-'0');
		compare[2]=(buffer[2]-'0');
		compare[3]=(buffer[3]-'0');
	
		for(c1=0;c1<4;c1++)
		{
			if(answer[c1]==compare[c1]) 
			{
				a+=1;
			}
		}
	
		for(c2=0;c2<=3;c2++)
		{
			for(c1=0;c1<=3;c1++)
			{
				if(compare[c1]==answer[c2] && c1!=c2)
				{
					b++;
				}
			}
		}			
	
		if(a==4)
		{
			message="Congratulations!!";
			write(sock , message, strlen(message)+1);
		}
		else
		{
			sprintf(message2,"%dA%dB",a,b);
			write(sock , message2, strlen(message2)+1);
			a=0;b=0;
		}
	}
   if (n < 0)
   {
      perror("ERROR writing to socket");
      exit(1);
   }
	
}
