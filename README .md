
# CS3.304 - Advanced Operating Systems
## Assignment - 1
#### How to run the code:

1.Compile the program with makefile:
```C++
make
```
2. Run the program:
```C++
./a
```
### Task 1
a shell prompt of the following form
will appear along with it. 
_username_@_system_name_:_current_directory_>
### Task 2
####cd
The cd command allows you to change the current directory. You can use the following options:

cd: Change to the home directory.
cd ..: Move up one directory.
cd -: Return to the previous directory not work as intended works to com back at home.
cd ~: Change to the home directory.
cd <directory>: Change to the specified directory.
####echo
The echo command is used to print text to the screen. It can handle spaces and tabs.
####pwd
The pwd command displays the current working directory.

### Task 3


The ls command lists files and directories. It supports the following options:

ls: List files and directories in a single column.
ls -a: List all files and directories, including hidden ones.
ls -l: List files and directories in a detailed format.
ls .: List the current directory.
ls ..: List the parent directory.
ls ~: List the home directory.
ls -a -l or ls -la: Combine multiple options.
ls <directory>: List files and directories in the specified directory.
ls -<flags> <directory>: Combine options and specify a directory.
it works on all commands


### Task 4
You can run both foreground and background processes:

Foreground processes will block the shell until they complete.
Background processes can be executed with the & symbol, and the shell will continue to take other commands.
### Task 5

The pinfo command displays information about the current shell process or a specified process by its PID.
#### note
but it works only first time  background process  with pid.
####task 6
The search command allows you to search for a given file or folder under the current directory recursively. It outputs either "True" or "False" depending on whether the file or folder exists.


