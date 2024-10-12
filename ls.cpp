#include <iostream>
#include <vector>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <iomanip>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
using namespace std;
void listFiles(const char* directory, bool showHidden, bool longFormat) {
    struct dirent* entry;
    DIR* dir;
   

    if ((dir = opendir(directory)) == 0) {
       cout<<"Invalid arguments"<<endl;
        return;
    }

    while ((entry = readdir(dir))!= NULL) {
        string name = entry->d_name;
        char timeString[50];
        off_t fileSize;
        struct tm* timeInfo;
        struct group* groupInfo; 
        struct passwd* ownerInfo;

        if (!showHidden && name[0] == '.') {
            continue; 
        }
        if (longFormat) {
            struct stat fileInfo;
            char path[PATH_MAX];
            snprintf(path, sizeof(path),"%s/%s",directory,name.c_str());

            if (stat(path, &fileInfo) == -1) {
                perror("stat");
                continue;
            }
            groupInfo=getgrgid(fileInfo.st_gid);
            ownerInfo=getpwuid(fileInfo.st_uid);
            fileSize = fileInfo.st_size;
            
            string perms= "----------"; // Use a character array, not a string literal
            mode_t mode=fileInfo.st_mode;

            if (S_ISDIR(mode)) {
                perms[0]='d';
            } else if (S_ISLNK(mode)) {
                perms[0]='l';
            }

            string permsChars = "rwxrwxrwx";
            for (int i=0;i<9;++i) {
                if ((mode&(1<<(8-i)))!=0) {
                    perms[i+1]=permsChars[i];
                }
            }
            
            timeInfo = localtime(&fileInfo.st_mtime);
            strftime(timeString, sizeof(timeString), "%b %d %H:%M", timeInfo);
          
            cout <<perms<< " "<<fileInfo.st_nlink<<" "<<ownerInfo->pw_name<<" "<<groupInfo->gr_name<<" "
                      <<setw(8)<<fileSize<<" "<<timeString<<" "<<name<<endl;
        } else {
            cout<<name<<" "<<endl;
        }
    }

    closedir(dir);
}
void lfile(const char* directory,const char* name, bool showHidden, bool longFormat) {
        char timeString[50];
        off_t fileSize;
        struct tm* timeInfo;
        struct group* groupInfo; 
        struct passwd* ownerInfo;

        if (!showHidden && name[0] == '.') {
            return; 
        }
        if (longFormat) {
            struct stat fileInfo;
            char path[PATH_MAX];
            snprintf(path, sizeof(path),"%s/%s",directory,name);

            if (stat(path, &fileInfo) == -1) {
                perror("stat");
                return;
            }
            groupInfo=getgrgid(fileInfo.st_gid);
            ownerInfo=getpwuid(fileInfo.st_uid);
            fileSize = fileInfo.st_size;
            
            string perms= "----------"; // Use a character array, not a string literal
            mode_t mode=fileInfo.st_mode;

            if (S_ISDIR(mode)) {
                perms[0]='d';
            } else if (S_ISLNK(mode)) {
                perms[0]='l';
            }

            string permsChars = "rwxrwxrwx";
            for (int i=0;i<9;++i) {
                if ((mode&(1<<(8-i)))!=0) {
                    perms[i+1]=permsChars[i];
                }
            }
            
            timeInfo = localtime(&fileInfo.st_mtime);
            strftime(timeString, sizeof(timeString), "%b %d %H:%M", timeInfo);
          
            cout <<perms<< " "<<fileInfo.st_nlink<<" "<<ownerInfo->pw_name<<" "<<groupInfo->gr_name<<" "
                      <<setw(8)<<fileSize<<" "<<timeString<<" "<<name<<endl;
        } else {
            cout<<name<<" "<<endl;
        }
    

   
}

int ls(string currentDir, vector<string>& tokens, int& i, int n) {
    bool showHidden = false;
    bool longFormat = false;
    vector<string> directories;

    for (; i < n; ++i) {
        const string& token = tokens[i];

        if (token == "ls") {
            continue;
        } else if(token=="-al"||token=="-la") {
            showHidden=true;
            longFormat=true;
        } else if(token=="-a") 
        {
            showHidden=true;
        } 
        else if (token=="-l") 
        {
            longFormat=true;
        } 
        else if (token=="~") 
        {
          directories.push_back(currentDir);
        } 
        else 
        {
         directories.push_back(token);
        }
    }

    if (directories.empty())
    {
        directories.push_back(currentDir);
    }

     for (const string& dirOrFile : directories) {
       
       

        struct stat fileInfo;
        if (stat(dirOrFile.c_str(), &fileInfo) == -1) {
            cout<<"invalid argument"<<endl;
            continue;
        }

        if (S_ISDIR(fileInfo.st_mode)) {
             cout << dirOrFile << endl;
            listFiles(dirOrFile.c_str(), showHidden, longFormat);
        } else if(S_ISREG(fileInfo.st_mode)) 
        {    
             lfile(get_current_dir_name(),dirOrFile.c_str(), showHidden, longFormat);
          
        }
        else 
        {
            cout<<"invalid path"<<endl;
        }
    }

    return 0;
}
