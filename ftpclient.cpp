#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SERV_TCP_PORT 8021
#define MAX 60
using namespace std;
int main(int arg,char*argv[])
{
	int sockfd,n;
	struct sockaddr_in serv_addr;
	struct hostent*server;
	char send[MAX],recvline[MAX],s[MAX],name[MAX];
}

