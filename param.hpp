/**
 *  param.hpp
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#ifndef _PARAM_HPP
#define _PARAM_HPP

/* Don't test program with more than this many tokens for input  */
#define MAXARGS 32

/* Class to hold input data                                  */
class Param
{
	private:
		char *inputRedirect;           /* file name or nullptr         */
		char *outputRedirect;          /* file name or nullptr         */
		int   background;              /* either 0 (false) or 1 (true) */
		int   argumentCount;           /* same as argc in main()       */
		char *argumentVector[MAXARGS+1]; /* array of strings             */
		
	public:
		
		/**
		 * Constructs an empty Param object.
		 */
		Param(); 

		/**
		 * Destructs the Param object.
		 */
		~Param();
		
		/**
		 * Adds an argument string to the argument list in this object. This function
		 * does not create a string copy of the original string. 
		 * 
         * @param newArgument a new argument to be added to the argument list; 
		 *                    if nullptr nothing will be added		 
         */
		void addArgument (const char* newArgument);
		
		/**
		 * Returns an argument list referencing char* strings. The last element in the 
		 * list is nullptr to mark the end of list elements. This makes the size of 
		 * the list one larger than the number of arguments added to this object.
		 * 
		 * Note: 
		 *   Caller must deallocate memory for the list.
		 */
		const char* const * getArguments();
	
		// getter & setter functions
		
		/**
		 * Sets the filename for input redirection.
		 *
		 * @param newInputRedirect a string specifying the input redirect filename
		 */
		void setInputRedirect(const char *newInputRedirect);
		
		/**
		 * Sets the filename for output redirection.
		 *
		 * @param newOutputRedirect a string specifying the output redirect filename
		 */
		void setOutputRedirect(const char *newOutputRedirect);
		
		/**
		 * Sets the value for the background proccessing flag
		 *
		 * @param newBackground an integar specifying the value for the background flag
		 * 1 indicates this process will run in the background
		 * 0 indicates this process will not run in the background
		 */
		void setBackground(int newBackground);
		
		/**
		 * Returns the filename for input redirection.
		 *
		 * @return a string representing a filename
		 */
		const char* getInputRedirect();
		/**
		 * Returns the filename for output redirection.
		 *
		 * @return a string representing a filename
		 */
		const char* getOutputRedirect();
		/**
		 * Returns the value of the background flag
		 *
		 * @return an int indicating the state of the flag
		 */
		int getBackground();
		
	
		/**
		 * Prints the information in the specified structure to standard out.
         */
		void printParams();
};

#endif
