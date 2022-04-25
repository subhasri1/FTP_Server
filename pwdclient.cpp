#include<iostream>
#include<stdio.h>
#include<math.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fstream>
#include <sys/stat.h> /*for getting file size using stat()*/
#include <sys/sendfile.h> /*for sendfile()*/
#include <fcntl.h> /*for O_RDONLY*/
#define SERV_TCP_PORT 8021
//int create_socket(int,char *);
//#define my_check(expr) (expr) ? ((void)0) : check(false)       
using namespace std;
int main(int arg,char*argv[])
{
	struct stat obj;
	int sockfd;
	int choice;
	char buf[100], command[5], filename[20], *f;
  	int k, size, status;
  	int filehandle;
	struct sockaddr_in serv_addr;// creating socket address
	struct hostent*server;
	//char sendline[MAXLINE],recvline[MAXLINE],s[MAXLINE],name[MAXLINE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);// creating socket
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        serv_addr.sin_port=htons(SERV_TCP_PORT);
		k = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	    //cout<<"\nEnter the source file name : \n";
	//    cin>>sendline;
	//     write(sockfd,sendline,MAXLINE);
	//    while((n=read(sockfd,recvline,MAXLINE))!=0)
			
	//        {
	//  	      send(sockfd,sendline, MAXLINE,0);
	//  	    }
		if(k == -1)
    	{
      		perror("Connect Error");
      		exit(1);
    	}
		int i=1;
		while(1)
		{
			cout<<"Enter a choice:\n1- pwd\n2- ls\n3-cd\n4-bye\n";
      		cin>>choice;
			switch(choice)
		    {
			  case 1:
		  	  {
	  			strcpy(buf, "pwd");//pwd as a command string stored in buf
	  			send(sockfd, buf, 100, 0); //pwd sent to the server
	  			recv(sockfd, buf, 100, 0); //receiving the path from server
	 			cout/*"The path of the remote directory is: %s\n"*/<<buf;
	 			break;
	  		  }
	  
			  case 2:
	  		  {
	  			strcpy(buf, "ls"); //ls command stored in buf
          		send(sockfd, buf, 100, 0); //ls sent to the server
				  cout<<"here";
	  			recv(sockfd, &size, sizeof(int), 0);//size of all the files in pwd
				  cout<<"here";
          		int *f = new int[size];//f = malloc(size);
          		recv(sockfd, f, size, 0);//client receives all the files 
	  			filehandle = creat("temp.txt", O_WRONLY);// creating a new file for storing all the file names to use in write function
	  			write(filehandle, f, size);//all files present in f are stored in filehandle
	  			close(filehandle);
         			cout<<" listing is as follows:\n";
	  			system("cat temp.txt");// printing all the contents of temp.txt on terminal output
	  			break;
	  		  }
			  case 3:
	  		  {
	  			strcpy(buf, "cd ");// storing cd command in buf
	 			cout<<"Enter the path to change :\n ";
	  			char path[50]; 
	  			cin>>path;
	  			sscanf(buf, "%s", path);
	  			send(sockfd, buf, 100, 0);// sending cd pathname to server
	  			recv(sockfd, &status, sizeof(int), 0);//client receiving pathname from the **client
          			if(status)
            				cout<<" successfully changed\n";
          			else
            				cout<<"failed to change\n";
          			break;
          	  }
			 case 4 :
			 {
			  	strcpy(buf, "bye");//for storing bye command in buffer 
			  	send(sockfd, buf, 100, 0);//sending bye command to the server
			  	recv(sockfd, &status, 100, 0);//client receives the termination status 
			  	if(status)
			    	{
			      		cout<<"Terminated\n";
			      		exit(0);
			    	}
			    	if (close(sockfd)==-1)
				    {
			   		   perror("Error in closing the socket");   
				    }
			 }
		
    	}
	}     
                  
                   //return 0;
	      
}
