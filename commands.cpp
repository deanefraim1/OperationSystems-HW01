//		commands.cpp
//********************************************
#include "commands.hpp"
#include <list>
#include "Job.hpp"
#include <string>
#include <iostream>

using namespace std;

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in OR external commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(list<Job> jobs, string lineSize, string cmdString)
{
	string cmd;
	string args[MAX_ARG];
	string pwd;
	string delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
	cmd = strtok(strdup(lineSize.c_str()), strdup(delimiters.c_str()));
	if(cmd.empty()) return 0; //TODO: or null returned from strtok???
	args[0] = cmd;
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, strdup(delimiters.c_str())); 
		if (!args[i].empty()) 
			num_arg++; 
 
	}


/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (cmd == "cd") 
	{
		
	} 
	
	/*************************************************/
	else if (cmd == "pwd") 
	{
		
	}
	
	/*************************************************/
	else if (cmd == "mkdir")
	{
 		
	}
	/*************************************************/
	
	else if (cmd == "jobs") 
	{
 		
	}
	/*************************************************/
	else if (cmd == "showpid") 
	{
		
	}
	/*************************************************/
	else if (cmd == "fg") 
	{
		
	} 
	/*************************************************/
	else if (cmd == "bg") 
	{
  		
	}
	/*************************************************/
	else if (cmd == "quit")
	{
   		
	} 
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		cout << "smash error: \"" << cmdString << "\"" << endl;
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(string args[MAX_ARG], string cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
					/* 
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();
					
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
			
			default:
                	// Add your code here
					/*
					your code
					*/
					int i = 0;
			}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(string lineSize)
{
	string ExtCmd;
	string args[MAX_ARG];
    if ((lineSize.find("|") != string::npos )
		 || (lineSize.find(">") != string::npos)
		 || (lineSize.find("<")!= string::npos)
		 || (lineSize.find("*") != string::npos)
		 || (lineSize.find("?") != string::npos)
		 || (lineSize.find(">>") != string::npos)
		 || (lineSize.find("|&") != string::npos))
    {
		// Add your code here (execute a complicated command)
					
		/* 
		your code
		*/
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(string lineSize, list<Job> jobs)
{

	string Command;
	string delimiters = " \t\n";
	string args[MAX_ARG];
	if (lineSize.back() == '&')
	{
		lineSize.pop_back();
		// Add your code here (execute a in the background)
		
		/* 
		your code
		*/
		
	}
	return -1;
}

