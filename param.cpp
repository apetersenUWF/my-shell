/**
 *  param.hpp
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#include <iostream>
#include <cstring>

#include "param.hpp"

using  namespace std;

Param::Param() 
{
	inputRedirect = outputRedirect = nullptr;
	background = 0;
	argumentCount = 0;
	
	// Might as well initialize every element to nullptr, as good practice.
	for (int i = 0; i <= MAXARGS; i++)
	{
		argumentVector[i] = nullptr;
	}
}

Param::~Param()
{
	// Since we are dealing with char * and char *[] class members, we must handle them properly in construction and destruction.
	delete[] inputRedirect;
	delete[] outputRedirect;

	inputRedirect = nullptr;
	outputRedirect = nullptr;

	int i = 0;

	// Since argumentVector is a char*[], we only call delete on the elements and not the array itself as its stored on the stack and not the heap.
	while (argumentVector[i])
	{
		delete[] argumentVector[i];
		argumentVector[i] = nullptr;

		i++;
	}
}

// I changed all of the parameter types from char * to const char * in all the the methods that pass in a string since it is best practice since we are not modifying
// whats passed in, rather we are just copying its value into the respective class member.
void Param::addArgument(const char *newArgument)
{
	if (argumentCount >= MAXARGS || newArgument == nullptr) return;

	// We should handle char * values this way in the case that a string stored in memory gets out of scope, ie. anything stored on the
	// stack since it will automatically be deleted later on, like string literals and const char * parameters.
	argumentVector[argumentCount] = new char[std::strlen(newArgument)+1]; // Allocate space for the new argument and +1 char for the null terminator character.
	std::strcpy(argumentVector[argumentCount], newArgument); // Copy newArgument onto the new argument element.

	argumentCount++;
}

// I changed the return type from char ** to const char* const * since I do not want the caller to be able to modify the array or its contents. The const char* part tells
// the compiler that each element in the return value should be immutable, and the const * tells the compiler that the returned array pointer itself should be immutable.
// This allows us to internally keep the array stored as a char *[] so we can modify it in the methods, while preventing the caller from modifying it directly, keeping
// everything clean and without using any weird type casting.
const char* const * Param::getArguments()
{
	if (argumentCount == 0) return nullptr;
	return argumentVector;
}

void Param::setInputRedirect(const char *newInputRedirect)
{
	if (newInputRedirect == nullptr) return;

	// Basically the same as how I did it in addArgument, except that we must delete the old value first since we are modifying in-place instead of appending to the array.
	delete[] inputRedirect;
	inputRedirect = new char[std::strlen(newInputRedirect)+1];
	std::strcpy(inputRedirect, newInputRedirect);
}

void Param::setOutputRedirect(const char *newOutputRedirect)
{
	if (newOutputRedirect == nullptr) return;

	delete[] outputRedirect;
	outputRedirect = new char[std::strlen(newOutputRedirect)+1];
	std::strcpy(outputRedirect, newOutputRedirect);
}
		
void Param::setBackground(int newBackground)
{
	background = newBackground;
}

// I changed the return values from char * to const char * in the next 2 methods so the caller can't access the class members directly and modify them, that would be really bad if they could.
const char* Param::getInputRedirect()
{
	return inputRedirect;
}
		
const char* Param::getOutputRedirect()
{
	return outputRedirect;
}
		
int Param::getBackground()
{
	return background;
}

void Param::printParams() {
	cout << "InputRedirect: [" 
	     << (inputRedirect != nullptr ? inputRedirect : "NULL");
	cout << "]" 
	     << endl 
		 <<	"OutputRedirect: [" 
		 << (outputRedirect != nullptr ? outputRedirect : "NULL");
	cout << "]" 
	     << endl 
		 << "Background: [" 
		 << background 
		 << "]" 
		 << endl 
		 << "ArgumentCount: [" 
		 << argumentCount 
		 << "]" 
		 << endl;
	for (int i = 0; i < argumentCount; i++)
		cout << "ArgumentVector[" 
			 << i 
			 << "]: [" 
			 << argumentVector[i] 
			 << "]" 
			 << endl;
}