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

void redirectOutput(const char* filename) {
    if (filename == nullptr) return;

    if (freopen(filename, "w", stdout) == nullptr) { //freopen redirects stdout or stdin to the provided filename, upon failure it returns nullptr
        perror("freopen failed to redirect stdout");
        _exit(EXIT_FAILURE);
    }

    // Learned about this online, essentially it copies stdout's file descriptor to stderr's, making stderr redirect to whatever stdout is redirected to.
    dup2(fileno(stdout), fileno(stderr));
}

void redirectInput(const char* filename) {
    if (filename == nullptr) return;

    if (freopen(filename, "r", stdin) == nullptr) {
        perror("freopen failed to redirect");
        _exit(EXIT_FAILURE);
    }
}

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

        if (debug) param.printParams();

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

            // Even if the fork fails, we should continue execution. 
        }
        else if (pid == 0) {
            //Must be the child process
            //I used execvp here because it takes the vector of arguments from the Param class cleanly and automatically searches the system to locate the program rather than requiring the path as an argument
            //execvp requires the final element of the argument vector to be null, meaning this will work up to MAXARGS - 1 arguments
            if (param.getOutputRedirect() != nullptr) { //redirect output
                redirectOutput(param.getOutputRedirect());
            }
            if (param.getInputRedirect() != nullptr) {//redirect input
                redirectInput(param.getInputRedirect());
            }
            execvp(args[0], args);  //searches system and executes the arguments specified by args
                                    //execvp should never return here because it was transformed into the new process
            perror("execvp failed");//if execvp returns it must have failed, print error message and terminate child
            _exit(EXIT_FAILURE);
        }
        else {
            //Must be the parent process

            //if this is a foreground process, wait before returning to the shell
            if (param.getBackground() == 0) waitpid(pid, nullptr, 0);

            // Otherwise, if the background flag is 1, continue execution as normal. The while(wait()) at the end of the program is what catches if a child is still running in the background when we try to exit.
        }

        delete[] inputbuf;
        inputbuf = nullptr;
    }

    // Wait until all child processes have exited
    while (wait(nullptr) > 0);

    return 0;
}