#include<iostream>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string>
#include<dirent.h>
#include<fstream>
using namespace std;
void validip(char *dir_name)
{
  DIR *dir;
  struct dirent *entry;
  string ip;
  fstream newfile;
  int flag=0;
  string tp;
  cout<< "enter a dummy ip address\n";
  getline(cin,ip);
  dir=opendir(dir_name);
  if(!dir)
  {
  cout<<"directory not found"<<endl;
  }
  else
  {
  while((entry=readdir(dir))!=NULL)
  {
      if(entry->d_name[0]!='.')
      {
        string path=string(dir_name)+"/"+string(entry->d_name);
        cout<<" \n"<<path<<endl;
        newfile.open("/var/myftp/blacklist_ip.txt",ios::in);
        if (newfile.is_open())
        {
           while(getline(newfile, tp))
           {

            if (tp.compare(ip)== 0)
            {

             flag=1;
             break;
            }
           }
           if(flag==1)
           {
             cout<<"blocked to access the server"<<endl;
           }
           else
           {
             cout<<"connection granted"<<endl;
           }
         }
         newfile.close();
         }
         }
         }
   closedir(dir);
}
int main()
{
validip((char*)"/var/myftp/");
 return 0;
}

