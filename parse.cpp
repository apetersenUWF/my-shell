#include <cstring>
#include "parse.hpp"
Param Parser::parse(char* input) {
  Param params;
  if (input == nullptr) return params;
  //delims epecifies the delimiters seperating each token of the command prompt
  const char delims[] = " \t\n";
  //first call of strtok will return a pointer the beginning of the first token and replace the first delimiter with a null terminating character
  //strtok will maintain a static internal pointer to the end of the last token after the first call
  char* token = strtok(input, delims);
  while (token != nullptr) {
    params.addArgument(token);
    //subsequent calls to strtok will return a pointer to the next token, replacing each delimiter with a null terminating character
    //subsequent calls should be made with nullptr as the argument because strtok will use its internal static pointer to reference the correct point in the string
    token = strtok(nullptr, delims);
    //when no more tokens are left, strtok will return nullptr
  }
  return params;
}