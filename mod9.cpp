#include<iostream>
#include<direct.h>
#include<unistd.h>
using namespace std;
while(fgets(sendline, MAXLINE,stdin)!=NULL)
{
	send(sockfd,sendline,MAXLINE,0);
	char *token,*dummy;
	dummy = sendline;
	token=strtok(dummy," ");
	if(strcmp ("quit\n",sendline)==0)
	{
		return 0;
	}
	else if(strcmp("ls\n",sendline)==0)
	{
		char buff[MAXLINE],check[MAXLINE]="1",port[MAXLINE];
		int data_port, datasock;
		recv(sockfd, port, MAXLINE, 0);
		data_port = atoi(port);
		datasock=create_socket(data_port,argv[1]);
		while(strcmp("1",check)==0);
		{
			recv(datasock,check,MAXLINE,0);
			if(strcmp("0",check)==0)
				break;
			recv(datasock, buff, MAXLINE,0);
			cout<<buff;

		}
	}
	else if(strcmp("!ls\n",sendline)==0)

	{
		system("ls);
		cout<<"\n";
	
	}
	else if(strcmp("pwd\n",sendline)==0)
	{
		char curr_dir[MAXLINE];
		recv9sockfd, curr_dir, MAXLINE,0);
		cout<<curr_dir<<endl;
	}

	else if(strcmp("!pwd\n",snedline)==0)
	{
		system("pwd");
	}
	else if(strcmp("cd",token)==0)
	{
		char check[MAXLINE];
		token=strtok(NULL,"\n");
		cout<<"Path given is: "<<token<<endl;
		recv(sockfd,check,MAXLINE,0)
		if(strcmp("0",check)==0)
		{
			cout<<"Directory does not exist. Check Path"<<endl;
		}
	}
	else if(strcmp("put",token)==0)
	{
		char port[MAXLINE], buffer[MAXLINE], char_num_blks[MAXLINE],char_num_last_blk[MAXLINE];
		int data_port,datasock,lsize,num_blks,num_last_blk,i;
		FILE *fp;
		recv(sockfd, port, MAXLINE, 0):
			data_port= atoi(port);
		datasock = create_socket(data_port, argv[1]);
		token strtok(NULL,"\n");
		if((fp=fopen(token,"r"))!=NULL)
		{
			send(sockfd, "1", MAXLINE,0);
			fseek(fp,0,SEEK_END);
			lsize=ftell(fp);
			num_blks=lsize/MAXLINE;
			num_last_blk=lsize%MAXLINE;
			cout<<char_num_blks<<"    "<<num_blks;
			send(sockfd, char_num_blks, MAXLINE,0);
			for(i =0;i<num_blks;i++)
			{
				fread(buffer, sizeof(char),MAXLINE,fp);
				send(datasock, buffer, MAXLINE,0);
			
			}
			cout<<char_num_last<<"  "<<num_last_blk;
			send(sockfd, char_num_last_blk, MAXLINE,0);
			if(num_last_blk>0)
			{
				fread(buffer, sizeof(char),num_last_blk,fp);
				send(datasock,buffer,MAXLINE,0);
			}
			fclose(fp);
			cout<<"File upload done"<<endl;
		}
		else
		{
			send(sockfd, "0", MAXLINE,0);
			cerr<<"Error in opening file. Check file name"<<endl;
		}
		else if (strcmp("get",token)==0)
		{
			char port[MAXLINE], buffer [MAXLINE], char_nu_blks[MAXLINE], char_num_last_blk[MAXLINE], message[MAXLINE];
			int data_port, datasock, lsize, num_blks, num_last_blk,i;
			FILE *fp;
			recv(sockfd, port, MAXLINE,0);
			data_port=atoi(port);
			datasock=create_socket(data_port, argv[1]);
			token=strtok(NULL," \n");
			if(strcmp("1", message)==0)
			{
				if((fp=fopen(token,"w"))==NULL)
					cout<<"Error i creating file"<<endl;
				else
				{
					recv(sockfd, char_num_blks, MAXLINE,0);
					num_blks=atoi(char_num_blks);
					for(i=0;i<num_blks;i++)
					{
						recv(datasock, buffer, MAXLINE,0);
						fwrite(buffer,sizeof(char), MAXLINE,fp);
					}
					recv(sockfd, char_num_last_blk, MAXLINE,0);
					num_last_blk=atoi(char_num_last_blk);
					if(num_last_blk>0)
					{
						recv(datasock, buffer, MAXLINE, 0)
							fwrite(buffer, sizeof(char),num_last_blk,fp);
					}
					fclose(fp);
					cout<<"File downloaded"<<endl;
				}
				else
				{
					cerr<<"Error in opening the file. Check file name "<<endl;
				}
			}
			else
			{
				cerr<<"Error in command. Check command."<<endl;
			}
			cout<<"ftp";
		}






