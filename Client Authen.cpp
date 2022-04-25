#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>


void userRegistration()
{
	string username, password;
	cout << "Enter Username : "; cin>>username;
	cout << "Enter Password : "; cin>>password;
	
	ofstream file("userlist.txt");
	file << username << endl << password;

	file.close();

}

bool isUser()
{

	string username, password, usnm, pssd;
	cout << "Enter Username : "; cin>>username;
	cout << "Enter Password : "; cin>>password;
	
	ifstream file("userlist.txt");
	getline(file, usnm);
	getline(file, pssd);

	if (usnm == username && pssd == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}




// client sends a string to the server and it recieves the  string with greetings from the server
int main()
{

	//socket creation
	int serv_fd = socket(AF_INET,SOCK_STREAM,0);
	if (serv_fd == -1)
	{
		perror("socket creation error");
		exit(1);
	}
	//initialize the socaddr_in structure
	struct sockaddr_in sock_addr_serv;// sockaddr_in for IPV4
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 8021;
	sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	// connecting to server
	socklen_t len = sizeof(sock_addr_serv);
	if (connect(serv_fd,(struct sockaddr *)&sock_addr_serv,len)==-1)
	{
		perror("connect error");
		exit(1);
	}	
	int choice ;
	cout << "  1.for Registration\n  2.for Login " << endl;
	cout << "Enter here : "; cin >> choice;
	if(choice == 2)
	{

		int loginAttempt=0, totalAttempt=5;
		while(loginAttempt < 5)
		{
			bool status = isUser();
			if(!status)
			{
          		cout << "Invalid login attempt. Please try again.\n" << '\n';
            	++loginAttempt;
            	cout << "Attempt Left : " << totalAttempt-loginAttempt << endl;

            	if (loginAttempt == totalAttempt)
    			{
           			cout << "Too many login attempts.....! \nThank you for logging in.\n";
           			exit(0);
           		}
           	}
			else
			{
				char ch[100], buf[100];
				cout << "enter a string : "; cin >> ch;
				send(serv_fd,ch,strlen(ch), 0);// writes a string to server
				int n =read(serv_fd,buf,sizeof(buf));// reads the acknowledgement from server
				write(1,buf,n);
				cout<<endl;
				break;
			}
		}
	}
	if(choice == 1)
	{
		userRegistration();
	}
close(serv_fd);
}









