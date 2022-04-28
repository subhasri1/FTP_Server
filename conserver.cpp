#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <signal.h>
// concurrent server

void transact_with_client(int sock);

//to avoid zombie process
void sighandler(int signum)
{
	cout << strsignal(signum) << endl;
	wait(NULL);
}

int main()
{

//signal disposition
signal(SIGCHLD, sighandler);

//socket creation
int serv_fd = socket(AF_INET,SOCK_STREAM,0);
if (serv_fd == -1)
{
	perror("socket creation error");
	exit(1);
}
//initialize the sockaddr_in structure
struct sockaddr_in sock_addr_serv;// sockaddr_in for IPV4
sock_addr_serv.sin_family = AF_INET;
sock_addr_serv.sin_port = 8021;
sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");

//bind the socket with ip address and port
if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
{
	perror("bind error");
	exit(1);
}

// listening (waiting) for client request
if (listen(serv_fd,5)==-1)
{
	perror("listen error");
	exit(1);
}

while (1)
{
	cout << "server waiting for client to connect"  << endl;
	
	//accepting client request
	struct sockaddr_in sock_addr_cli;
	socklen_t cli_len = sizeof(sock_addr_cli);
	int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	
	//cout << "clinet port no. " << sock_addr_cli.sin_port << endl;
	
 	if (client_fd==-1)
	{
		perror(" accept error");
		exit(1);
	}
	
	pid_t pid= fork();
	if (pid==0)
	{
		transact_with_client(client_fd);
		exit(0);
	}
	else if (pid > 0)
	{
		close(client_fd);
	}
	else
	{
		perror("error in fork");
		exit(1);
	}	
}	

//close socket
if (close(serv_fd)==-1)
{
	perror("socket close error");
	exit(1);
}
}
void transact_with_client(int sock)
{
	char ch[100];
	read(sock,ch,sizeof(ch));
	puts(ch);
	char greet[]={"hello "};
	strcat(greet,ch);
	write(sock,greet,strlen(greet));	
	
}
