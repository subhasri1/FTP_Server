#include<iostream>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string>
#include<dirent.h>
using namespace std;
void explore(char *dir_name)
{
  DIR *dir;
  struct dirent *entry;
  struct stat info;
  dir=opendir(dir_name);
  if(!dir)
  {
    cout<<"directory was not found\n"<<endl;
    return;
  }
  while((entry=readdir(dir))!=NULL)
  {
    if(entry->d_name[0]!='.')
    {
      cout<<dir_name<<endl;
      cout<<entry->d_name<<" ";
    }
   }
   closedir(dir);
}
int main()
{
 string user;
 cout<<"enter user type="<<endl;
 cin>>user;
 if(user=="anonymous")
 {
explore((char*)"/var/myftp/pub_directory");
}
else
{
cout<<"not ananonymous user"<<endl;
}
return 0;
}
