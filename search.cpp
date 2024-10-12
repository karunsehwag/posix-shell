#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
bool search(string& file,const fs::path& currentDir) {
 
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if(entry.is_regular_file()) {
            if (entry.path().filename()==file) {
                return true; 
            }
        }
        else if (entry.is_directory()) {
            if (entry.path().filename()==file) {
                return true;
            }
            if (search(file,entry)) {
                return true; 
             }
          }  
    }
    return false; 
}


