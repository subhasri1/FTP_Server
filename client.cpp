#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include "include/userauth.h"
#define MAXLINE 4096
using namespace std;

//to avoid zombie process
void sighandler(int signum)
{
	cout << strsignal(signum) << endl;
	wait(NULL);
}


void transact_with_serv(int);
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
	//cout<<"Connected successfully!!"<<endl;
	if(argc==1)
	{
		cout<<"Connected successfully"<<endl;
		cout<<"Welcome Anonymous"<<endl;
		cout<<"ftp>";
		//exit(1);
	}
	else if(argc==2)
	{

		string s(argv[1]);
		if(isuser(s))
		{
			cout<<"ftp>";
			transact_with_serv(sockfd);
		}
		else
		{
			cout<<"Invalid details";
			exit(1);
		}
		
	}

	else
	{
		cout<<"Usage: ./client or ./client username "<<endl;
		exit(1);
	}


	
	close(sockfd);
}
void transact_with_serv(int sock)
{	
	//string user,pass;
	//char sendline[MAXLINE],recvline[MAXLINE];
	//char ch=',';
	char buf[100];
	int n;
	
	while(1)
	{
		//authen();
	/*cout<<"Enter username:";
	cin>>user;
	cout<<"Enter password:";
	cin>>pass;
	*/
	
	/*strcat(buf,user.c_str());
	strcat(buf,",");
	strcat(buf,pass.c_str());
	*/
	send(sock,buf,strlen(buf),0);
	cout<<"Message sent"<<endl;
	n=recv(sock,buf,sizeof(buf),0);
		
	//write(1,buf,n);

	cout<<"ftp>";	
	}
}


