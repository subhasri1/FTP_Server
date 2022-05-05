//FTP Server
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include <vector>
#include "include/userauth.h"       //Header file consisting of function declaration and definition
using namespace std;
#define SIZE 100
//Concurrent server
ofstream slog("serv.log",ios::app);	//Creating and Opening log file	
string transact_with_client(int);   //Declaring the transaction with client operation
void listdir(int);					//For ls
void copyput(int);					//For put	
void copyget(int ,string);			//For get
void impl(int);						//Processing of functionality for registered user and anonymous
ofstream ofs;
char home_dir[SIZE];				//Storing the home directory
//main function
int main()
{		
		slog<<"[INFO]:Main function started\n";
     	signal(SIGCHLD, sighandler);     //Binding SIGCHLD with sighandler function
    	
		//Socket creation
		slog<<"[INFO]:Creating socket\n";
		int sockfd=socket(AF_INET,SOCK_STREAM,0);
    	if(sockfd==-1)
    	{
    		slog<<"[ERROR]:Socket creation\n";
       		 perror("Socket error");
       		 exit(1);
    	}
    	
		struct sockaddr_in serv_addr;
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_port=8021;        //Registering to port 8021
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		//Binding the socket to the address and port
		slog<<"[INFO]:Binding the socket\n";
		if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		{
			slog<<"[ERROR]:Binding the socket\n";
			perror("Binding error");
			exit(1);
		}
		//Listen to the process on socket for communication(here up to 5)
		slog<<"[INFO]:Listening socket\n";
		if(listen(sockfd,5)==-1)
		{
			slog<<"[ERROR]:Listening socket\n";
			perror("Error in listen");
			exit(1);
		}
		//Server waiting for clients to connect
		slog<<"[INFO]:Server waiting for clients to connect\n";
		while(1)
		{
			
			cout<<"Server waiting for client to connect....."<<endl;
			//Creating a new socket
			slog<<"[INFO]:New socket created\n";
			struct sockaddr_in cli_addr;
			socklen_t cli_len=sizeof(cli_addr);
			//Block until the client connects to the server
			slog<<"[INFO]:Accepting connections\n";
			int clifd=accept(sockfd,(struct sockaddr*)&cli_addr,&cli_len);
			if(clifd==-1)
			{
				slog<<"[ERROR]:Accepting any client connection\n";
				perror("Accept error");
				exit(1);
			}
			//Handshaking with client
	 		slog<<"[INFO]:Checking validity of IP address\n";
			string ip=inet_ntoa(cli_addr.sin_addr);
			cout<<ip<<endl;
			bool v=validip(ip);        //Checking the IP address is valid or not
			char msg[SIZE];
    		int n=0;
    		char opt[10];
			if(v==true)
			{
				slog<<"[INFO]:IP address is valid\n";
				read(clifd,opt,sizeof(opt));
    			strcpy(msg,"Connection established..."); 
    			int n=write(clifd,msg,strlen(msg));  //send1
    			bzero(msg,sizeof(msg));
    			slog<<"[INFO]:Creating child process\n";
				pid_t pid= fork();         //Creating the child process
				if (pid==0)
				{
					slog<<"[INFO]:Child process is running\n";
					if (strcmp(opt,"1")==0)
					{
						slog<<"[INFO]:Anonymous user\n";
						strcpy(home_dir,"/home/anonymous/ftp/var/pub");
						impl(clifd);
					}
					else
					{
						slog<<"[INFO]:Registered user\n";
						cout<<opt<<endl;
						string username=transact_with_client(clifd);
						cout<<"auth user"<<"\t"<<username<<endl;
						strcpy(home_dir,"/home/");
						strcat(home_dir,username.c_str());
						impl(clifd);
						char cmd[30]="";
					}
				}
				else if (pid > 0)           //Parent process
				{
					slog<<"[INFO]:Parent process is running\n";
					close(clifd);
				}
				else
				{
					slog<<"[ERROR]:Fork Error\n";
					perror("Error in fork");
					exit(1);
				}
			}
			else
			{
				slog<<"[ERROR]:Black Listed IP address found\n";
	 			strcpy(msg,"black listed ip"); 
		       	n = send(clifd,msg,strlen(msg),0); 
	    	}
	} // end of while
	//Closing the socket
	if(close(sockfd)==-1)
	{
		slog<<"[ERROR]:Socket closing error\n";
		perror("Error in socket class");
		slog<<"[ERROR]:Exiting\n";
		exit(1);
	}
	slog.close();
}

//Performing transactions with client
string transact_with_client(int sock)
{
		slog<<"[INFO]:Starting transactions with client function\n";
		char user[SIZE];        //Username
		char buf[SIZE];        //Buffer
		char pass[SIZE];        //Password
		int n;					
		memset(buf,'\0',sizeof(buf));  //Clearing the buffer
		slog<<"[INFO]:Receiving username from client\n";
		n=recv(sock,buf,sizeof(buf),0);//Receiving username from client and storing in buf
		buf[n]='\0';
		slog<<"[INFO]:Sending Received as acknowledgement to the client\n";
		n=send(sock,"Received",8,0);   //Sending "Received" to client
		strcpy(user,buf);              //Copying the username stored in buf
		bzero(buf,sizeof(buf));        //Initialize the buf to zero		
		slog<<"[INFO]:Username and password checking.....\n";
		while (1)
		{
			slog<<"[INFO]:Receiving the password\n";
			n=recv(sock,buf,sizeof(buf),0);//Receiving the password and storing to buf
			buf[n]='\0';
			strcpy(pass,buf);               //Copying the password stored in buf
			bzero(buf,sizeof(buf)); 
			slog<<"[INFO]:Checking the username and password\n";
			bool b=validate(user,pass);     //Getting the status of validation
			if(b==false)
			{
				slog<<"[ERROR]:Either username or password or both are wrong\n";
				strcpy(buf,"Login unsuccessful");
				send(sock,buf,strlen(buf),0);
				strcpy(user,"");
			}
			else
			{
				slog<<"[INFO]:Successful login\n";
				strcpy(buf,"Login successful");
				send(sock,buf,strlen(buf),0);
				break;
			}
		}
	return user;
}

void listdir(int clifd)
{
	slog<<"[INFO]:List directory function started\n";
	vector<string> files=explore(home_dir);
	cout<<"home_dir is "<<home_dir<<endl;
	char msg[SIZE];
	files.push_back("end");
	for(string file: files)
	{
		strcpy(msg,file.c_str());
		int n=write(clifd,msg,strlen(msg)); 
		bzero(msg,sizeof(msg)); 
		n=read(clifd,msg,sizeof(msg));
		bzero(msg,sizeof(msg));
	}
	slog<<"[INFO]:List directory function ended\n";
}

void copyput(int sd)	
{	
	slog<<"[INFO]:copyput function started\n";
	int n=0;
	char buf[SIZE];
	while(1)
	{
		n=read(sd,buf,sizeof(buf));
		buf[n]='\0';
		if (strcmp(buf,"end")==0)
			break;
		else
		{
		    ofs<<buf;
		    write(sd,"received",8);
		}
	}
	slog<<"[INFO]:copyput function ended\n";
}

void copyget(int sd ,string fn)
{	
	slog<<"[INFO]:copyget function started\n";
	ifstream ifs;
	ifs.open(fn);
	string data;
	cout << "in copy get "<< fn << endl;
	char buf[SIZE];
	while(!ifs.eof())
	{
		getline(ifs, data);
		data=data+"\n";
		write(sd,data.c_str(),data.length());
		read(sd,buf,sizeof(buf));
		bzero(buf,sizeof(buf));
	}
	write(sd,"end",3);
	ifs.close();
	slog<<"[INFO]:copyget function ended\n";
}

void impl(int clifd)						
{
	slog<<"[INFO]:Implementation function started\n";
	char cmd[30]="";
	char cmd1[30]="";
	while(1)
	{
		bzero(cmd1,sizeof(cmd1));
		bzero(cmd,sizeof(cmd));
		int n=read(clifd,cmd1,sizeof(cmd1)); //getting command from user
		strncpy(cmd,cmd1,3);
		if (strcmp(cmd,"pwd")==0)
		{
				slog<<"[INFO]:PWD\n";
		   	  	printdir(clifd,home_dir);
		}
		else if(strcmp(cmd,"ls")==0)
		{
				slog<<"[INFO]:LS\n";
				listdir(clifd);
		}
		else if(strcmp(cmd,"bye")==0)
		{
				slog<<"[INFO]:QUIT\n";
				exit(0);
		}
		else if (strcmp(cmd,"put")==0)
		{
				slog<<"[INFO]:Uploading \n";
				char *cmd2=strtok(cmd1," ");
				cout<<"before "<<cmd2<<endl;
				char *fn=strtok(NULL,"");
				char fname[SIZE];				//file name
				strcpy(fname,home_dir);		
				cout<<home_dir<<" "<<fn<<endl;	
				strcat(fname,"/");
				strcat(fname,fn);
				ofs.open(fname);
				write(clifd,"received",8);
				copyput(clifd);
				ofs.close();
				slog<<"[INFO]:Uploading done\n";
		}
		else if (strcmp(cmd,"get")==0)
		{
				slog<<"[INFO]:Downloading\n";
				char *cmd2=strtok(cmd1," ");
				cout << "before "<< cmd2 << endl;
				char *fn=strtok(NULL,"");
				char fname[SIZE];
				strcpy(fname,home_dir);
				cout<<home_dir<<" "<<fn<<endl;
				strcat(fname,"/");
				strcat(fname,fn);
				copyget(clifd,fname);
				slog<<"[INFO]:Downloading done\n";
		}
	}
	slog<<"[INFO]:Implementation function ended\n";		
}



