#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "include/userauth.h"
using namespace std;
void transact_with_serv(int sock)
{	
	char buf[100];
	int n;
	while(1)
	{
	cout<<"ftp>";
	fgets(buf,100,stdin);
	send(sock,buf,strlen(buf),0);
	n=recv(sock,buf,sizeof(buf),0);
	

	write(1,buf,n);

	
	}
}

int main(int argc,char* argv[])
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("error in socket");
		exit(1);
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=8021;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	{
		perror("Error connection");
		exit(1);
	}
	if(argc==1)
	{
		cout<<"Welcome Anonymous"<<endl;
		cout<<"ftp>";
		//exit(1);
	}
	else if(argc==2)
	{

	
	
		cout<<"ftp>";
		authen();
	transact_with_serv(sockfd);


	}
	else
	{
		cout<<"Usage: ./client or ./client username "<<endl;
		exit(1);
	}
	close(sockfd);
}

