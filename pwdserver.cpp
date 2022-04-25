//FTP SERVER
#include<iostream>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#define SERV_TCP_PORT 8021
//#define MAX 100
using namespace std;
// int i, j, tem;
// char buff[4096], t;
// FILE *f1;
int main(int afg, char *argv[])
{
       struct sockaddr_in server, client;
       struct stat sfile;
       int sockfd, newsockfd;
       char buf[100], command[5], filename[20];
       int k, i, size, c;
       int filehandle;
       socklen_t clength;
       struct sockaddr_in serv_addr,cli_addr;
       //char t[MAX], str[MAX];
       //strcpy(t,"exit");
       if(sockfd == -1)
       {
            cout<<"Socket creation failed";
           exit(1);
       }
       sockfd=socket(AF_INET, SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       cout<<"\n socket with  the local server.......";
       k=bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       cout<<"\naccept client connection request...";
       listen(sockfd, 5);
       clength=sizeof(cli_addr);
       newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
       //  close(sockfd);
       // read(newsockfd,&str,MAX);
       //    cout<<"\nClient message inside \n File Name :"<<str<<endl;
       //    f1=fopen(str,"r");
           
       // if(f1==NULL)
       // {
	// 	perror("Error in opening file");
		
       
       // }
       // while(fgets(buff,4096,f1)!=NULL)
       // {
	//        write(newsockfd, buff,MAX);
	//        cout<<"\n";
       // }
       i=1;
        while(1)
        {
           recv(newsockfd, buf, 100, 0);
           sscanf(buf, "%s", command);
           if(!strcmp(command, "pwd"))
	    {
	       system("pwd>temp.txt");
	       i = 0;
             FILE*f = fopen("temp.txt","r");
              while(!feof(f))
                  buf[i++] = fgetc(f);
             buf[i-1] = '\0';
	     fclose(f);
            send(newsockfd, buf, 100, 0);
	   }
          else if(!strcmp(command, "ls"))
	   {
	      system("ls > temp.txt");
	      i = 0;
	      stat("temp.txt",&sfile);//
	      size = sfile.st_size;
	      send(newsockfd, &size, sizeof(int),0);
	      filehandle = open("temp.txt", O_RDONLY);
	      sendfile(newsockfd,filehandle,NULL,size);//NULL- so that the client can edit the file
	   }
          else if(!strcmp(command, "cd "))
          {
             if(chdir(buf+3) == 0)
	        c = 1;
	      else
	        c = 0;
            send(newsockfd, &c, sizeof(int), 0);
          }
          else if(!strcmp(command, "bye"))
	   {
	      //cout<<"Terminated"<<endl;
	      i = 1;
	      send(newsockfd, &i, sizeof(int), 0);
	      exit(0);
	   }
      }
       // fclose(f1);
       // cout<<"\nFile Transferred\n";
       return 0;
}
