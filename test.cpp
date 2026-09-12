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
    int testParser() {
      Parser parser;
      cout << "Enter a string to parse\n";
      cout << ">>>: ";
      char input[1024];
      cin.getline(input, sizeof(input));
      Param param = parser.parse(input);
      param.printParams();
      //finish more tests
     return 0;
    }
    int testParam() {
      Param params;
      const char* const * args = params.getArguments();
      if (args != nullptr) return -1;
      const char* s1 = "cat";
      const char* s2 = "dog";
      params.addArgument(s1);
      params.addArgument(s2);
      const char* const * args2 = params.getArguments();
      if (args2[0] == nullptr) return -1;
      if (strcmp(args2[0], "cat") != 0) return -1;
      params.printParams();
      return 0;
    }
};

#endif