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
int map1(string name,string pass)
{
	map<string,string> m1
	{
		{"kailash","kailash"},
		{"kiran","Kiranunique"},
		{"aadhish","aaaddd"}
	};
	
	for(auto it= m1.begin();it!=m1.end();++it)
	{
	
	if(user==it->first&&pass==it->second)
		return 1;
	else
		return 0;
	
	}
}

int main(int argc, char *argv[])
{
       int sockfd, newsockfd;
       socklen_t clength;
       struct sockaddr_in serv_addr,cli_addr;
       char str[MAX];
       if(argc!=2)
       {
		perror("Usage: ./a.out <port number>");
		exit(1);
       }
       strcpy(t,"bye");
       sockfd=socket(AF_INET, SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       if(atoi(argv[1])!=8021)
       {
		perror("Please enter the correct port(must be 8021)");
		exit(1);
       }
 
       cout<<"\n socket with  the local server.......";
       bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       cout<<"\naccept client connection request...";
       listen(sockfd, 5);
       clength=sizeof(cli_addr);
       newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
       close(sockfd);
       read(newsockfd,&str,MAX);
       cout<<"\nClient message inside \n File Name :"<<str<<endl;

       f1=fopen(str,"r");
       if(f1==NULL)
       {
		perror("Error in opening file");
		
       
       }
       while(fgets(buff,4096,f1)!=NULL)
       {
	       write(newsockfd, buff,MAX);
	       cout<<"\n";
       }
       fclose(f1);
       cout<<"\nFile Transferred\n";
       return 0;
}
