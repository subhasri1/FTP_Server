#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<syslog.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include "include/userauth.h"
using namespace std;
void transact_with_client(int);



int main(int args,char* argv[])
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
		else
		{
	 	//handshaking with client
	 	char msg[]="Successfull Connection established from the Server\n";
	 	
	 	write(clifd,&msg,sizeof(msg));
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

void transact_with_client(int sock)
{
//		ofstream fout;
//		fout.open("data.txt");
		char user[30];
		char buf[100];
		char pass[30];
		int n;
		memset(buf,'\0',sizeof(buf));
		n=recv(sock,buf,sizeof(user),0);
		
		strcpy(user,buf);
		cout<<user;
		/*
		if(authen(user,pass))
		{
			n=recv(sock,pass,sizeof(pass),0);
			strcpy(pass,buf);	
		}
		//memset(buf,'\0',sizeof(buf));
		
		
		if()
			
			int i=0;
			int j;
			while(buf[i]!=',')
			{	user+=buf[i];
				i++;
				j=i;
			}
			while(buf[j]<strlen(buf))
			{
				pass+=buf[j];
				j++;
			}


			write(1,buf,n);
			//send(sock,user.c_str(),n,0);
			//send(sock,pass.c_str(),n,0);
			send(sock,buf,n,0);
			//fout.close();	
		
*/
}



