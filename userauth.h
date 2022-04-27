#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<syslog.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<map>
using namespace std;
//bool authen(string,string);
static void skeleton_daemon();
bool isuser(string);
void registr();
void attempt();

//bool loginValidate(string,string);

//Kailash----------
static void skeleton_daemon()
{
	pid_t pid,sid;
	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}
	sid=setsid();
	if(sid<0)
	{
		exit(EXIT_FAILURE);
	}
	signal(SIGCHLD,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid=fork();
	if(pid<0)
	{
		exit(EXIT_FAILURE);
	}
	if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	chdir("/");
	int x;
	for(x=sysconf(_SC_OPEN_MAX);x>=0;x--)
	{
		close(x);
	}
	openlog("firstdaemon",LOG_PID,LOG_DAEMON);
}

bool isuser(string uname)
{
	ifstream fin;
	fin.open("users.txt");
	if(!fin)
	{
		cerr<<"Error in opening file"<<endl;
		exit(1);
	}
	else
	{
	string name,pass;

		getline(fin,name);
		//fin>>name;
		if(name==uname)
		{
			string p;
			cout<<"Enter password";
			cin>>p;
			getline(fin,pass);
			//cout<<pass;
			if(p==pass)
			{//fin>>pass;
			cout<<"Authentication successful\nWelcome "<<uname;
			
			}
			else
			{
				int count=2;
				while(count>=0)
				{	
					cout<<"Attempt no. "<<3-(count+1)<<endl;	
					attempt();
					count--;
				}
				if(count==0)
				{
					cout<<"Attempt exceeded......Exiting"<<endl;
				}
			}	
		}
	
	else
	{
		registr();	
		fin.close();	
	}
}
}

void attempt()
{
					string p;
					cout<<"\nEnter the password again:";
					cin>>p;
						
						
}
/*
bool authen(string name,string pass)
{
	int loginAttempt = 0;
	bool uservalid=false;
    string userName,userPassword;
	ifstream fin;
	fin.open("users.txt"); 	
	while (!fin.eof())) 
	{
    		if()// input them into the map 
	}
       
	do{
		 // cout<<"Enter userName:";
          //cin>>userName;
		for(it=m.begin();it!=m.end();++it)
   		{	if(userName ==  name && userPassword == pass)
        	{
		
            	cout<<"Welcome "<<userName<<"\n";
				uservalid=true;
				
				return true;	
        		break;
			}
			else
			{
				cerr<<"Invalid user"<<endl;
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
			return false;
		}
	}
	
	}while(!uservalid&&loginAttempt<3);
	fin.close();
    //cout << "Thank you for logging in.\n";
	
}
*/

void registr()
{
		string reguser,regpass;
		cout<<"===NEW USER REGISTRATION==="<<endl;
	    cout<<"Enter username:";
	    cin>>reguser;
	    cout<<"Enter password:";
	    cin>>regpass;
		ofstream fout;
		fout.open("users.txt",ios::app);
        fout<<reguser<<endl<<regpass<<endl;//' '<<regname<<' '<<regmobile<<' '<<regemail<<' '<<regaddress<< 
      	fout.close();	
}




/*bool loginValidate(string user,string pass)
{
     int count;
        string u,p;
        ifstream fin("users.txt");
       	while(fin>>u>>p)
        {
                if(u==user && p==pass)
                {
                        count=1;

                }
        }
        fin.close();
        if(count==1)
        {
            
                return true;

        }
        else
        {
          	return false;
        }
}
*/
