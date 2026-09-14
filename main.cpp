#include "param.hpp"
#include "parse.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <cstring>

using namespace std;

bool debug = false;

int main(int argc, char *argv[]) {
    // -Debug flag check
    for (int i = 1; i < argc; i++) {
        // I could've used strcmp(...) == 0 instead of string_view() but idk modern features are nice
        if (string_view(argv[i]) == "-Debug") {
            debug = true;
        }
    }

    cout << "myshell - part 1" << endl;

    // This is just a temporary debug mode indicator for part 1
    if (debug) {
        cout << "Debug mode is on." << endl;
    }
    else {
        cout << "Debug mode is off." << endl;
    }

    Parser parser;
    string input;
    char *inputbuf = nullptr;

    // Main loop
    while (true) {
        cout << ">>>: ";
        getline(cin, input);

        // Check before its parsed
        if (input == "exit") break;
        
        // A set size char[] would have been just fine, but I went this route so nothing gets truncated.
        inputbuf = new char[input.length() + 1];
        strcpy(inputbuf, input.c_str());

        Param param = parser.parse(inputbuf);
        if (debug) param.printParams();

        delete[] inputbuf;
        inputbuf = nullptr;
    }
}