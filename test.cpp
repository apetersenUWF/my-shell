#ifndef TEST_CPP
#define TEST_CPP

#include "param.hpp"
#include "parse.hpp"
#include <iostream>
#include <cstring>
using namespace std;

class Test {
  private:
  public:
    int test() {
      Parser parser;
      while (true) {
        cout << "Enter a string to parse\n";
        cout << ">>>: ";
        char input[1024];
        cin.getline(input, sizeof(input));
        Param param = parser.parse(input);
        param.printParams();
      }
     return 0;
    }
};

#endif