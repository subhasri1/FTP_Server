//FTP Client
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<vector>
#include "include/userauth.h"           //Header file consisting of function declaration and definition
using namespace std;
bool transact_with_serv(int,char*);     //Declaring the transaction with server operation
#define SIZE 200

//Command-line argument
int main(int argc,char* argv[])
{
    //Socket creation
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("Error in socket");
		exit(1);
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=8021;             //Registering to port 8021
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	//Establishing connection to the server
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	{
		perror("Error connection");
		exit(1);
	}
	char buf[SIZE]="";                      //Buffer
    char command[30]="";
    char ack[20]="";
    strcpy(ack,"received");
	if(argc==1)                             //Anonymous user
	{
		write(sockfd,"1",1);
		int n = read(sockfd,buf,sizeof(buf)); // for connection establishment
		buf[n]='\0';
		cout<<buf<<endl;						//"connection established"
		bzero(buf,sizeof(buf));
		//call the implementation
		impl(sockfd,argc);
	}	
	else if(argc==2)                        //Registered user
	{	write(sockfd,"2",1);
		read(sockfd,buf,sizeof(buf));
		cout<<buf<<endl;
		bool b=transact_with_serv(sockfd,argv[1]);
		if (b==true)
		{
			
			impl(sockfd,argc);
		}
	}
	else
	{
		cout<<"Usage: ./client or ./client username "<<endl;
		exit(1);
	}
	close(sockfd);
}
bool transact_with_serv(int sock,char* name)
{

	char buf[100];                      //Buffer
	char buf1[100];                     //Buffer to store command
	char *command=strtok(buf1," ");
	int n;                              //Store the no of characters
	char pass[30];                      //Password
	
	n=send(sock,name,strlen(name),0);   //Sending name to the server
	n=recv(sock,buf,sizeof(buf),0);     //Receiving the acknowledgement
	int flag=1;
	bool b=false;
	while(flag<=3)                       //No of attempts for entering password is 3
	{
		cout<<"Enter password:";
		
		cin.getline(pass,30,'\n');
		
		send(sock,pass,strlen(pass),0);     //Sending password to the server
		n=recv(sock,buf,sizeof(buf),0);     //Receiving the acknowledgement
		buf[n]='\0';
		
	 	cout<<buf<<endl;
		if(strcmp(buf,"Login successful")==0)
		{
	       	  b=true;
			  break;
		}
		else 								// if login is not successful
		{
			flag++;
		}
	}
	return b;

}


