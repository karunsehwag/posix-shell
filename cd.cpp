#include <iostream>
#include<vector>
#include <unistd.h> // Include this header for chdir
#include <string>
using namespace std;
void remove(string currentdir,string & str)
{
                    size_t found = str.find(currentdir);
                     if (found != std::string::npos) {
                     str.erase(found, currentdir.size());
                     }
}
int cd(string currentdir,vector<string>& tokens,string& prompt,int &i, int n, string username, string systemName)
{  
    string str=get_current_dir_name();
           if(i>=n || tokens.size() == 1)
           {  
             if(chdir(currentdir.c_str())==0)
                {   prompt.clear();
                   str=get_current_dir_name();
                    prompt = username + "@" + systemName +":~>";
                }
              
           }
            else if (tokens[i]==";"||tokens[i]=="~"||tokens[i]=="-") {
               cout<<"2";
                if(chdir(currentdir.c_str())==0)
                {   prompt.clear();
                   str=get_current_dir_name();
                    prompt = username + "@" + systemName +":~>";
                }
                if(tokens[i]=="-")
                  cout<<get_current_dir_name()<<endl;
                i++;
            } 
            else if(tokens[i]==".."&&currentdir.compare(str)==0)
            {   i++;
               cout<<get_current_dir_name()<<endl;
            }
            else if(tokens[i]=="..")
            {  if(chdir("..")==0)
                  { 
                   prompt.clear();
                   str=get_current_dir_name();
                   if(str.size()>=currentdir.size())
                   {
                   remove(currentdir,str);
                   prompt = username+"@"+systemName + ":~"+str+">";
                   }
                   }
                   else 
                      {
                         prompt = username+"@"+systemName + ":~"+str+">";
                      }
                   i++;  
             }
            else
            {    if(chdir(tokens[i].c_str())==0)
                   { prompt.clear();
                   str=get_current_dir_name();
                   if(str.size()>=currentdir.size())
                   {
                   remove(currentdir,str);
                   prompt = username+"@"+systemName + ":~"+str+">";
                   }
                   else 
                      {
                         prompt = username+"@"+systemName + ":~"+str+">";
                      }
                      i++;
                   }
            }

return 0;
}
