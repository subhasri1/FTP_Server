#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "include/userauth.h"
using namespace std;
void authen()
{
	map<string,string> m = {{"kailash","chandra"},{"lash","chand"},{"Guru","dra"},{"anonymous",""}};
	int loginAttempt = 0;
	bool uservalid=false;
   	string userName,userPassword;
	map<string,string> :: iterator it;
	do{
		  cout<<"Enter userName:";
          	  cin>>userName;
               	  cout<<"Enter userPassword:";
          	  cin>>userPassword;
	for(it=m.begin();it!=m.end();++it)
    	{	if(userName ==  it->first && userPassword == it->second)
        	{
            	cout<<"Welcome "<<userName<<"\n";
		uservalid=true;
        	break;
		}
	}
	if(!uservalid)
	{
		loginAttempt++;
		cout<<(3-loginAttempt)<<" attempts left.... "<<endl;
    		cout << "Invalid login attempt. Please try again.\n";
		if(loginAttempt==3)
		{
			cout<<"Attempts completed!!!"<<endl;
		}
	}
	
	}while(!uservalid&&loginAttempt<3);

    //cout << "Thank you for logging in.\n";
	
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
		exit(1);
	}
	else if(argc==2)
	{
	cout<<"ftp>";
	
	authen();

		
	char buf[100];
	cout<<"ftp>";
	fgets(buf,100,stdin);
	write(sockfd,buf,100);
	
	read(sockfd,buf,100);

	cout<<"from server "<<buf<<endl;

	}
	else
	{
		cout<<"Usage: ./client or ./client username "<<endl;
		exit(1);
	}
	close(sockfd);
}
