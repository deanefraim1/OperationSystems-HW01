/*	smash.cpp
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <csignal>
#include "commands.hpp"
#include "signals.hpp"
#include "Job.hpp"
#include <iostream>
#define MAX_LINE_SIZE 80
#define MAXARGS 20

using namespace std;

list<Job> jobs; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
string prompt;
string cwd;
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    string cmdString;

	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp
	 /* add your code here */
	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp
	//set your signal handlers here
	/* add your code here */

	/************************************/

	/************************************/
	// Init globals 


	
	
    	while (1)
    	{
	 	cout << "smash > ";
		getline(cin, prompt);
		cmdString = prompt;
					// perform a complicated Command
		if(!ExeComp(prompt)) continue; 
					// background command	
	 	if(!BgCmd(prompt, jobs)) continue; 
					// built in OR external commands
		ExeCmd(jobs, prompt, cmdString);
		
		/* initialize for next line read*/
		prompt.clear();
		cmdString.clear();
		}
	return 0;
}

