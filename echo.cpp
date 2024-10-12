#include <iostream>
#include <string>
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;

void echo(const string& cmd) {
    int  echoPos=cmd.find("echo");
    int startp,texts,endq ;
    string text;
        startp= echoPos + 4;
        texts= cmd.find_first_not_of(" \t", startp);
        text=cmd.substr(texts,endq-texts);
        cout<<text<<endl;
      
    }
