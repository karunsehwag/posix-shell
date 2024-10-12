#include <iostream>
#include<vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <cstring>
#include <limits.h> 

using namespace std;


string getVirtualMemory(int pid) {
    ifstream statusFile("/proc/" + to_string(pid) + "/status");
    string vmsize;
    string line;
   
    if (statusFile.is_open()) {
        
        while (getline(statusFile, line)) 
        {
            if (line.find("VmSize:") == 0) {
                vmsize = line.substr(8);
                break;
            }
        }
        statusFile.close();
    }
    return vmsize;
}

string getExecutablePath(int pid) {
    ssize_t exePathLength;
    char exePath[PATH_MAX];
    exePathLength=readlink(("/proc/"+to_string(pid) + "/exe").c_str(),exePath,sizeof(exePath) - 1);
    if (exePathLength!=-1) {
        exePath[exePathLength]='\0';
        return exePath;
    }
    return "";
}
string getProcessStatus(int pid) {
    string status;
     string line;
    ifstream statusFile("/proc/"+to_string(pid)+"/status");
    if (statusFile.is_open()) {
       
        while (getline(statusFile, line)) {
            if (line.find("State:")==0) {
                status=line.substr(7);
                break;
            }
        }
        statusFile.close();
    }
    return status;
}


int info(vector<string>& tokens,int& i,int n) {
    string exec,sys,user;
    if (i>=n) {
       
        struct utsname unameData;
        uname(&unameData);
        
        user=getenv("USER");
        sys=unameData.nodename;
        exec=getExecutablePath(getpid());
        
        cout<<"pid -- " << getpid()<<endl;
        cout<<"Process Status -- {"<<getProcessStatus(getpid())<<"}"<<endl;
        cout<<"memory -- "<<getVirtualMemory(getpid())<<"{Virtual Memory}"<<endl;
        cout<<"Executable Path -- "<<exec<<endl;
    } else{
       
        int pid=stoi(tokens[i]);
        i++;

        exec=getExecutablePath(pid);
        
        if (!exec.empty()) {
            cout<<"pid -- "<<pid<<endl;
            cout<<"Process Status -- {"<<getProcessStatus(pid)<<"}"<<endl;
            cout<<"memory -- "<<getVirtualMemory(pid)<<"{Virtual Memory}"<<endl;
            cout<<"Executable Path -- "<<exec<<endl;
        } 
        else 
        {
            cout<<"Process with PID "<<pid<<" not found."<<endl;
            return 1;
        }
    } 

    return 0;
}
