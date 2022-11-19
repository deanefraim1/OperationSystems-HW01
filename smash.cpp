/*	smash.cpp
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <csignal>
#include "commands.hpp"
#include "signals.hpp"
#include "Job.hpp"
#include <iostream>
#include "Shell.hpp"

using namespace std;

Shell shell;
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    string cmdString;
	string prompt;
	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp

	struct sigaction int_signal;
	struct sigaction stp_signal;

	int_signal.sa_handler = SignalHandler_ctrZ;
	stp_signal.sa_handler = SignalHandler_ctrC;

	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp
	//set your signal handlers here

	sigaction(SIGINT,  &int_signal,  NULL);
    sigaction(SIGTSTP, &stp_signal,  NULL);

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
	 	if(!BgCmd(prompt)) continue; 
					// built in OR external commands
		ExeCmd(prompt, cmdString);

		/* initialize for next line read*/
		prompt.clear();
		cmdString.clear();
	}
	return 0;
}

