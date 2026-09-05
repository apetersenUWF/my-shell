#include "param.hpp"
#include <iostream>
int main() {
  Param parameter;
  char* s1 = "cat\0";
  char* s2 = "dog\0";
  parameter.addArgument(s1);
  parameter.addArgument(s2);
  char** args = parameter.getArguments();
  parameter.printParams();
  return 0;
}