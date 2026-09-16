#include "parse.hpp"
#include <string_view>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <cstring>

using namespace std;

bool debug = false;

int main(int argc, char *argv[]) {
    // -Debug flag check
    for (int i = 1; i < argc; i++) {
        if (string_view(argv[i]) == "-Debug") {
            debug = true;
        }
    }

    Parser parser;
    string input;
    char *inputbuf = nullptr;

    while (true) {
        cout << ">>>: ";
        getline(cin, input);

        // Check before its parsed
        if (input == "exit") break;
        
        inputbuf = new char[input.length() + 1];
        strcpy(inputbuf, input.c_str());

        Param param = parser.parse(inputbuf);
        char* const * args = param.getArguments();
        //check first if args is empty
        if (args == nullptr || args[0] == nullptr) {
            //if empty, clean up and return to terminal
            delete[] inputbuf;
            inputbuf = nullptr;
            continue;
        }
        pid_t pid = fork(); //duplicate process and store child pid
        
        if (pid < 0) {//fork failed
            perror("Fork Failed");
            delete[] inputbuf;
            return -1;
        }
        else if (pid == 0) {
            //Must be the child process
            //I used execvp here because it takes the vector of arguments from the Param class cleanly and automatically searches the system to locate the program rather than requiring the path as an argument
            //execvp requires the final element of the argument vector to be null, meaning this will work up to MAXARGS - 1 arguments
            execvp(args[0], args); 
            perror("execvp failed");
        }
        else {
            //Must be the parent process
            if (param.getBackground() == 0) waitpid(pid, NULL, 0); //if this is a foreground process, wait before returning to the shell
            else {
                //background process
                //can possibly track background pids in an array
                //finish
            }
        }
        if (debug) param.printParams();

        delete[] inputbuf;
        inputbuf = nullptr;
    }
    return 0;
}