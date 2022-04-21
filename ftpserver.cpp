//FTP SERVER
#include<iostream>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SERV_TCP_PORT 8021
#define MAX 100
using namespace std;
int i, j, tem;
char buff[4096], t;
FILE *f1;
int main(int afg, char *argv[])
{
       int sockfd, newsockfd;
       socklen_t clength;
       struct sockaddr_in serv_addr,cli_addr;
       char t[MAX], str[MAX];
       strcpy(t,"exit");
       sockfd=socket(AF_INET, SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       cout<<"\nBinded";
       bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       cout<<"\nListening...";
       listen(sockfd, 5);
       clength=sizeof(cli_addr);
       newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
       close(sockfd);
       read(newsockfd,&str,MAX);
       cout<<"\nClient message\n File Name :"<<str<<endl;
       f1=fopen(str,"r");
       if(f1==NULL)
       {
		perror("Error in opening file");
		
       }
       fclose(f1);
       cout<<"\nFile Transferred\n";
       return 0;
}
