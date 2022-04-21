#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
<<<<<<< HEAD
#include<arpa/inet.h>
=======
>>>>>>> 527f7853883dba2ecef044da42317245ee93c238
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SERV_TCP_PORT 8021
#define MAX 60
using namespace std;
int main(int arg,char*argv[])
{
	int sockfd,n;
	struct sockaddr_in serv_addr;
	struct hostent*server;
	char send[MAX],recvline[MAX],s[MAX],name[MAX];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
<<<<<<< HEAD
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(SERV_TCP_PORT);
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))== -1)
	{
		perror("coonection error");
		exit(1);
	}
	cout<<"\nEnter the source file name : \n";
	cin>>send;
	write(sockfd,send,MAX);
	while((n=read(sockfd,recvline,MAX))!=0)
	{
		cout<<recvline;
	}
	close(sockfd);
	return 0;
}


=======
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        serv_addr.sin_port=htons(SERV_TCP_PORT);
        connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
}
>>>>>>> 527f7853883dba2ecef044da42317245ee93c238
