#include<string.h>
#include<iostream>
#include<map>
using namespace std;
void authen()
{
	map<string,string> m = {{"kailash","chandra"},{"lash","chand"},{"Guru","dra"},{"anonymous",""}};
	int loginAttempt = 0;
	bool uservalid=false;
    string userName,userPassword;
    //int flag=0;
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
				//flag=1;		
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
			flag=0;
		}
	}
	
	}while(!uservalid&&loginAttempt<3);
	return flag;
    //cout << "Thank you for logging in.\n";
	
}
