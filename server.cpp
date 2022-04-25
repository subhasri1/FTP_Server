#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<syslog.h>
#include<fcntl.h>
using namespace std;
static void skeleton_daemon()
{
	pid_t pid,sid;
	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}
	sid=setsid();
	if(sid<0)
	{
		exit(EXIT_FAILURE);
	}
	signal(SIGCHLD,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	chdir("/");
	int x;
	for(x=sysconf(_SC_OPEN_MAX);x>=0;x--)
	{
		close(x);
	}
	openlog("firstdaemon",LOG_PID,LOG_DAEMON);
}
void transact_with_client(int sock)
{

		char buf[100];
		int n;
		memset(buf,'\0',sizeof(buf));
		while((n=recv(sock,buf,sizeof(buf),0))>0)
			send(sock,buf,n,0);
	

}
int main()
{
	skeleton_daemon();

	int sockfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=8021;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	{
		perror("Binding error");
		exit(1);
	}
	if(listen(sockfd,5)==-1)
	{
		perror("Error in listen");
		exit(1);
	}

	
	while(1)
	{
		
		cout<<"Server waiting for client to connect....."<<endl;
		struct sockaddr_in cli_addr;
		socklen_t cli_len=sizeof(cli_addr);
		int clifd=accept(sockfd,(struct sockaddr*)&cli_addr,&cli_len);
		cout<<"client port :"<<cli_addr.sin_port<<endl;
		if(clifd==-1)
		{
			perror("Accept error");
			exit(1);
		}
		transact_with_client(sockfd);

	}
	
	if(close(sockfd)==-1)
	{
		perror("Error in socket class");
		exit(1);
	}
	while(1)
	{
		syslog(LOG_NOTICE,"First daemon terminated");
		sleep(20);
		break;
	}
	syslog(LOG_NOTICE,"First daemon terminated");
	closelog();
	//return EXIT_STATUS;
}
