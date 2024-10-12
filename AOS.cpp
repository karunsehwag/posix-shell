#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib> // Add this header for getenv()
#include <cstddef> // Add this header for size_t
#include "cd.cpp"
#include "ls.cpp"
#include "search.cpp"
#include <filesystem>
#include "echo.cpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <algorithm>
#include "pipinfo.cpp"
namespace fs = std::filesystem;

using namespace std;
vector<int> backgroundProcesses;

vector<string> tokenizeInput(const string& input) {
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


int main() {
    struct utsname data;
    uname(&data);
    string username,systemName,prompt,currdir ;
    username=getenv("USER");
    systemName=data.nodename;
    prompt=username + "@" + systemName + ":~>";
    currdir=get_current_dir_name();

    while (true) {
        int start,end;
        string input;
     
        cout << prompt;
         vector<string> commands;
        
        getline(cin, input);
        start = 0;
        while ((end = input.find(';', start)) != string::npos) {
            commands.push_back(input.substr(start, end - start));
            start = end + 1;
        }
        commands.push_back(input.substr(start));

        for (const string& cmd : commands) {
            vector<string> tokens = tokenizeInput(cmd);
            int n = tokens.size();
            int i = 0;
            if (cmd == "exit") {
                for (int pid : backgroundProcesses) {
                    kill(pid, SIGTERM);
                }
                return 0;
            }

            while (n > i) {
                if (tokens[i]=="exit") {
                    return 0;
                } else if (tokens[i]=="cd") {
                    i++;
                 cd(currdir, tokens, prompt, i, n, username, systemName);
                } else if (tokens[i]=="pwd") {
                    i++;
                    cout << get_current_dir_name() << endl;
                    continue;
                } else if (tokens[i]=="ls") {
                    i++;
                    ls(currdir, tokens, i, n);
                }
                else if(tokens[i]=="search")
                {   i++;
                      fs::path curr = fs::current_path();
                     if (search(tokens[i],currdir)) {
                          std::cout << "True" << std::endl;  
                           } else {
                           std::cout << "False" << std::endl;
                           }
              i++;     }
    
                else if(tokens[i]=="echo")
                {
                    echo(cmd);
                  
                   i=n+1;
                }else if(tokens[i]=="pinfo")
                {
                    i++;
                    info(tokens,i,n);
                }
                else {
                                   bool runInBackground = false;
                                   pid_t childPid;
                                   vector<char*> args;
    if (tokens[n - 1] == "&") {
        runInBackground = true;
        tokens.pop_back(); // Remove '&' symbol
    }


    
    for (const string& token : tokens) {
        args.push_back(const_cast<char*>(token.c_str()));
    }
    args.push_back(nullptr); // Null-terminate the array
    childPid = fork();

    if (childPid < 0) {
        cout<<"cant open fork"<<endl;
    } else if (childPid == 0) {
        
        execvp(args[0], args.data());
        cerr << "INVALID COMMAND" << endl;
        exit(1);
    } else {
       
        if (runInBackground) {
          
            cout<<childPid<<endl;
        } else {
           
         waitpid(childPid, nullptr, 0);
        }
    }

                    i = n + 1; 
                }
            }
        }
    }

    return 0;
}
