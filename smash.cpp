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

Shell *shell;
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
	shell = new Shell();
	string prompt;
	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp

	struct sigaction intSignal;
	struct sigaction stpSignal;

	intSignal.sa_handler = SignalHandler_ctrC;
	intSignal.sa_flags = SA_RESTART;
	stpSignal.sa_handler = SignalHandler_ctrZ;
	stpSignal.sa_flags = SA_RESTART;

	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.cpp
	//set your signal handlers here

	sigaction(SIGINT,  &intSignal,  NULL);
    sigaction(SIGTSTP, &stpSignal,  NULL);

	/************************************/
	
	
	/************************************/
	// Init globals

	while (1)
	{
		cout << "smash > ";
		getline(cin, prompt);		
		ExeCmd(prompt);
		/* initialize for next line read*/
		prompt.clear();
	}
	delete(shell);
	return 0;
}

