#include <cstring>
#include "parse.hpp"
Param Parser::parse(char* input) {
    Param params;
    if (input == nullptr) return params;
    //delims specifies the delimiters seperating each token of the command prompt
    const char delims[] = " \t\n";
    const char outputRedirectFlag = '>';
    const char inputRedirectFlag = '<';
    const char backgroundFlag[] = "&";
    //first call of strtok will return a pointer the beginning of the first token and replace the first delimiter with a null terminating character
    //strtok will maintain a static internal pointer to the end of the last token after the first call
    char* token = strtok(input, delims);
    while (token != nullptr) {
        if (token[0] == outputRedirectFlag) {//token contains the output redirect flag
            if (strlen(token) == 1) {//output redirect flag is the only character of the token, must be followed by a delimiter, next token must be the file
                token = strtok(nullptr, delims);
                if (token != nullptr)
                    params.setOutputRedirect(token);
                //otherwise the file was not included with the flag, this is invalid and will cause the flag to be ignored
            }
            else {//redirect flag is not followed by a delimiter, rest of the token is the file
                params.setOutputRedirect(token + 1);
            }
        }
        else if (token[0] == inputRedirectFlag) {//token contains the input redirect flag
            if (strlen(token) == 1) {//input redirect flag is the only character of the token, must be followed by a delimiter, next token must be the file
                token = strtok(nullptr, delims);
                if (token != nullptr)
                    params.setInputRedirect(token);
                //otherwise the file was not included with the flag, this is invalid and will cause the flag to be ignored
            }
            else {//redirect flag is not followed by a delimiter, rest of the token is the file
                params.setInputRedirect(token + 1);
            }
        }

        else if (strcmp(token, backgroundFlag) == 0) {//token is the background process flag
            params.setBackground(1);
            //background process flag must be the final token, return params after setting the flag
            break;
            //if more characters are included with the background flag, this will be added to the argument vector and not trigger the flag
            //if more tokens follow the background flag they will be ignored
        }
     
        else { //token is not a flag, add it as an argument
            params.addArgument(token);
        }
        //subsequent calls to strtok will return a pointer to the next token, replacing each delimiter with a null terminating character
        //subsequent calls should be made with nullptr as the argument because strtok will use its internal static pointer to reference the correct point in the string
        token = strtok(nullptr, delims);
        //when no more tokens are left, strtok will return nullptr
    }
    return params;
}