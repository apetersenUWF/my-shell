#include "param.hpp"
#include "parse.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void test_parse() {
    Parser parser;
    char input[1024];
    
    while (true) {
        cout << "Enter a string to parse\n";
        cout << ">>>: ";
        
        cin.getline(input, 1024);

        Param param = parser.parse(input);
        param.printParams();
    }
}

int main() {
    test_parse();
}