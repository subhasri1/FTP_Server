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
#include<syslog.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<dirent.h>
#include<string.h>
#include <vector>
#include "include/userauth.h"
#define SIZE 200
using namespace std;
//Check whether the username and password are valid or not
bool validate(char* uname,char* pass)
{
	
	ifstream fin;
	fin.open("users.txt");
	if(!fin)
	{
		perror("Error in opening file");
		exit(1);
	}
	else
	{
		char name[30],password[30];
		fin>>name>>password;
		cout<<"From validate"<<endl;
		cout<<name<<" "<<uname<<endl;
		cout<<pass<<" "<<password<<endl;
		do
		{
		if((strcmp(name,uname)==0) && (strcmp(pass,password)==0))
		{

			return true;
		}
		fin>>name>>password;

		}while(!fin.eof());

		return false;
	}

	fin.close();
}



//Checking the IP address is blacklisted or not
bool validip(string ip)
{
	//ofstream  log=logger.getofsLog();
	//log << "[INFO]: validating the ipnaddress \n";
	fstream newfile;
	int flag=0;
	string line;
	newfile.open("blacklist_ip.txt",ios::in);
	if (newfile.is_open())
	{
		   while(getline(newfile, line))
		   {
			    if (line.compare(ip)== 0)
			    {

				     flag=1;
				     break;
			    }
		   }
		   if(flag==1)
		   {
		   		return false;
		   }
		   else
		   {
		  	 	return true;
		   }
		   newfile.close();
	}
	else
	{	// log << "[ERROR]: validating the ipnaddress \n";
		 perror(" error in opening the file");
		 exit(1);
	}
  
}

//Listing the files present in pub directory
vector<string> explore(char *dirname)
{
  DIR *dir;
  struct dirent *entry;		
  struct stat info;
  dir=opendir(dirname);
  vector<string> filevector;
  cout << "explore" << dirname << endl;
  if(!dir)
  {
    cout<<"directory was not found\n"<<endl;
    
  }
  while((entry=readdir(dir))!=NULL)
  {
  	 //cout << entry->d_name << endl;
   	 if(entry->d_name[0]!='.') 
         	filevector.push_back(entry->d_name);
  
  }
  closedir(dir);
 // for(string s:filevector)
  //	cout << s << endl;
  return filevector;
}


//Creating files in Upload directory
void upload()
{
  DIR *dir;
  struct dirent *entry;
  fstream file;
  string s,s1,s2,s3;
  cout<<"enter name of file to be created"<<endl;
  cin>>s;
  s2="/home/anonymous/ftp/var/pub";
  s3=s2.append(s);
  dir=opendir("/home/anonymous/ftp/var/pub");
  if(!dir)
  {
    cout<<"directory was not found\n"<<endl;
    return;
  }
     file.open(s3,ios::out);
     if(file.is_open())
     {
        cout<<"enter the content in file"<<endl;
        cin>>s1;
       file<<s1<<endl;
       file.close();
       cout<<"file write operation completed"<<endl<<endl;
     }
      else
      {
      cout<<"unable to create a  file"<<endl;
      }
      while((entry=readdir(dir))!=NULL)
      {
      if(entry->d_name[0]!='.')
      {
      cout<<"/home/anonymous/ftp/var/pub"<<endl;
      cout<<entry->d_name<<" "<<endl;

      }
      }
   closedir(dir);
}

//Listing the files present in home directory
void explorehome()
{
  DIR *dir;
  struct dirent *entry;
  struct stat info;
  dir=opendir("/home/kailash");
  if(!dir)
  {
    cout<<"directory was not found\n"<<endl;
    return;
  }
  while((entry=readdir(dir))!=NULL)
  {
    if(entry->d_name[0]!=NULL)
    {
      cout<<"/home/kailash"<<endl;
      cout<<entry->d_name<<" "<<endl<<endl;
    }
   }
   closedir(dir);
}

//Creating files in home directory of registered user
void uploadhome()
{
  DIR *dir;
  struct dirent *entry;
  fstream file;
  string s,s1,s2,s3;
  cout<<"enter name of file to be created"<<endl;
  cin>>s;
  s2="/home/kailash";
  s3=s2.append(s);
  dir=opendir("/home/kailash");
  if(!dir)
  {
    cout<<"directory was not found\n"<<endl;
    return;
  }
     file.open(s3,ios::out);
     if(file.is_open())
     {
        cout<<"enter the content in file"<<endl;
        cin>>s1;
       file<<s1<<endl;
       file.close();
       cout<<"file write operation completed"<<endl<<endl;
     }
      else
      {
      cout<<"unable to create a  file"<<endl;
      }
      while((entry=readdir(dir))!=NULL)
      {
      if(entry->d_name[0]!='.')
      {
      cout<<"/home/kailash"<<endl;
      cout<<entry->d_name<<" "<<endl;

      }
      }
   closedir(dir);
}

//FTP client function implementation
void impl(int sockfd,int argc)
{
		
	    	char command[30]="";
	    	char cmd[SIZE];
	    	char ack[20]="";
	    	strcpy(ack,"received");
			char buf[SIZE];	
			int n=0;
			bzero(buf,sizeof(buf));		
			while(1)
			{
				cout << "ftp>";
				bzero(cmd,sizeof(cmd));
				bzero(command,sizeof(command));
				cin.getline(cmd,SIZE,'\n');
				strncpy(command,cmd,3);
				//sending the command to the server
				if (strcmp(command,"put")==0)
					write(sockfd,cmd,strlen(cmd));
				else if (strcmp(command,"get")==0)
				{
					if (argc==1)
						cout << "invalid command " << endl;
					else
						write(sockfd,cmd,strlen(cmd));
				}
				else	
					write(sockfd,command,strlen(command));
					if(strcmp(command,"pwd")==0)
					{
						bzero(buf,sizeof(buf));
						n=read(sockfd,buf,sizeof(buf));//recv3
						buf[n]='\0';
						cout << buf << endl;
					}
					else if (strcmp(command,"ls")==0)
					{
						while(1)
						{	
							bzero(buf,sizeof(buf));			
							n=read(sockfd,buf,sizeof(buf));//reading the files sent by server
							write(sockfd,ack,strlen(ack));
							if(strcmp(buf,"end")!=0)
							{	
								cout << buf << endl;
								bzero(buf,sizeof(buf));	
						
							}
							else
							{
								break;
							}
						}
				
					}
					else if (strcmp(command,"bye")==0)
					{
						exit(0);
					}
					else if (strcmp(command,"put")==0)
					{
						char *cmd1=strtok(cmd," ");
						char *fn=strtok(NULL,"");
						ifstream ifs;
						ifs.open(fn);
						string data;
						read(sockfd,buf,sizeof(buf));
						while(!ifs.eof())
						{
							getline(ifs, data);
							data=data+"\n";
							write(sockfd,data.c_str(),data.length());
							read(sockfd,buf,sizeof(buf));
							bzero(buf,sizeof(buf));
						}
				
						write(sockfd,"end",3);
						ifs.close();
					}
					else if ((strcmp(command,"get")==0) && argc!=1)
					{
						char *cmd1=strtok(cmd," ");
						char *fn=strtok(NULL,"");
						ofstream ofs;
						ofs.open(fn);
						char buf[SIZE];
						while(1)
						{
							n=read(sockfd,buf,sizeof(buf));
							buf[n]='\0';
							if (strcmp(buf,"end")==0)
								break;
							else
							{
		   						ofs<<buf;
		   						cout<<buf<<endl;
		    					write(sockfd,"received",8);
							}
						}
						ofs.close();
						bzero(buf,sizeof(buf));
						bzero(command,sizeof(command));
					}
				}	
}
//FTP server function for printing directory
void printdir(int clifd, char* dir)
{
	int n=write(clifd,dir,strlen(dir)); //send3
	//bzero(dir,sizeof(dir));  
}
//To avoid zombie process
void sighandler(int signum)
{
	cout << strsignal(signum) << endl;
	wait(NULL);
}

