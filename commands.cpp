//		commands.cpp
//********************************************
#include "commands.hpp"
#include <vector>
#include "Job.hpp"
#include <string>
#include <iostream>
#include "Shell.hpp"
#include <regex>

using namespace std;

extern Shell *shell;

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in OR external commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************

int ExeCmd(string prompt)
{
	string cmd;
	string args[MAX_ARG];
	string delimiters = " \t\n";  
	int num_arg = 0;
	bool illegal_cmd = false; // illegal command
	char *tmp = strtok(strdup(prompt.c_str()), strdup(delimiters.c_str()));
	if(tmp != NULL)
		cmd = tmp;
	if(cmd.empty()) return 0; //TODO: or null returned from strtok???
	args[0] = cmd;
	for (int i = 1; i < MAX_ARG; i++)
	{
		char *currentArg = strtok(NULL, strdup(delimiters.c_str()));
		if(currentArg == NULL)
			break;
		args[i] = currentArg;
		num_arg++;
	}

	/*************************************************/
	// Built in Commands PLEASE NOTE NOT ALL REQUIRED
	// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
	// MORE IF STATEMENTS AS REQUIRED
	/*************************************************/
	if (cmd == "cd") 
	{
		if(num_arg == 1)
		{
			if(args[1] == "..")
			{
				string newPwd = shell->pwd.substr(0, shell->pwd.find_last_of('/'));
				if (chdir(newPwd.c_str()) == ERROR)
					illegal_cmd = true;
				else
				{
					shell->lastPwd = shell->pwd;
					shell->pwd = newPwd;
				}
			}
			else if(args[1] == "-")
			{
				if(shell->lastPwd.empty())
					cout << "smash error: cd: OLDPWD not set" << endl;
				else
				{
					chdir(shell->lastPwd.c_str());
					swap(shell->pwd, shell->lastPwd);
				}
			}
			else 
			{
				if(chdir(args[1].c_str()) == ERROR)
					illegal_cmd = true;
				else
				{
					shell->lastPwd = shell->pwd;
					shell->pwd = args[1];
				}
			}
		}
		else
		{
			cout << "smash error: cd: too many arguments" << endl;
		}
	}

	/*************************************************/
	else if (cmd == "pwd") 
	{
		cout << shell->pwd << endl;
	}

	/*************************************************/
	else if (cmd == "mkdir")
	{
 		//No need to impliment.
	}
	/*************************************************/
	
	else if (cmd == "jobs") 
	{
		for (int i = 0; i < shell->jobs.size(); i++)
		{
			cout << "[" << shell->jobs[i].jobID << "] " << shell->jobs[i].command << " : " << shell->jobs[i].PID << " " << shell->jobs[i].secondElapsed << "secs";
			if(shell->jobs[i].status == stopped)
				cout << "(stopped)";
			cout << endl;
		}
	}
	/*************************************************/
	else if (cmd == "showpid") 
	{
		cout << "smash pid is " << getpid() << endl;
	}
	/*************************************************/
	else if (cmd == "fg") 
	{
		if (num_arg == 0)
		{
			if(shell->jobs.empty())
				cout << "smash error: fg: jobs list is empty" << endl;
			else 
				shell->MoveJobToFg(shell->jobs.end());
		}
			
		else if((num_arg != 1) || (!regex_match(args[1], regex("(\\d)+"))))
			cout << "smash error: fg: invalid arguments" << endl;
		else
		{
			int jobIDToFg = atoi(args[1].c_str());
			int jobIndexToFg = shell->GetJobIndexByJobID(jobIDToFg);
			if(jobIndexToFg == NOT_EXCIST)
				cout << "smash error: fg: job-id " << jobIDToFg << " does not exist " << endl;
			else
			{
				shell->MoveJobToFg(shell->jobs.begin() + jobIndexToFg);
			}
		}
	}
	/*************************************************/
	else if (cmd == "bg") 
	{
  		if(num_arg == 0)
		{
			int stoppedJobPIDWithMaxJobID = shell->GetStoppedJobPIDWithMaxJobID();
			if (stoppedJobPIDWithMaxJobID == NOT_EXCIST)
				cout << "smash error: bg: there are no stopped jobs to resume" << endl;
			else
			{
				shell->jobs[stoppedJobPIDWithMaxJobID].status = running;
				kill(stoppedJobPIDWithMaxJobID, SIGCONT);
			}
		}
		else if((num_arg != 1) || (!regex_match(args[1], regex("(\\d)+"))))
			cout << "smash error: bg: invalid arguments" << endl;
		else
		{
			int jobIndexToBg = shell->GetJobIndexByJobID(atoi(args[1].c_str()));
			if (jobIndexToBg == NOT_EXCIST)
				cout << "smash error: bg: job-id " << args[1] << " does not exist" << endl;
			else if(shell->jobs[jobIndexToBg].status != stopped)
				cout << "smash error: bg: job-id " << args[1] << " is already running in the background" << endl;
			else
			{
				shell->jobs[jobIndexToBg].status = running;
				kill(shell->jobs[jobIndexToBg].PID, SIGCONT);
			}
		}
	}
	/*************************************************/
	else if (cmd == "quit")
	{
   		
	}
	else if (cmd == "kill")
	{
		if(num_arg != 2 || !regex_match(args[1], regex("-(\\d)+")) || !regex_match(args[2], regex("(\\d)+")))
			cout << "smash error: kill: invalid arguments" << endl;
		else
		{
			int sigNum = atoi(args[1].substr(1, args[1].length()).c_str());
			int jobID = atoi(args[2].c_str());
			int jobIndexToKill = shell->GetJobIndexByJobID(jobID);
			if(jobIndexToKill == NOT_EXCIST)
				cout << "smash error: kill: job-id <" << jobID << "> does not exist" << endl;
			else
			{
				kill(shell->jobs[jobIndexToKill].PID, sigNum);
				cout << "signal number " << sigNum << "was sent to pid " << shell->jobs[jobIndexToKill].PID << endl;
			}
		}
	}
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmd);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		cout << "smash error: \"" << prompt << "\"" << endl;
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
void ExeExternal(string args[MAX_ARG], string cmd)
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
					i++;
			}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(string prompt)
{
	string ExtCmd;
	string args[MAX_ARG];
    if ((prompt.find("|") != string::npos )
		 || (prompt.find(">") != string::npos)
		 || (prompt.find("<")!= string::npos)
		 || (prompt.find("*") != string::npos)
		 || (prompt.find("?") != string::npos)
		 || (prompt.find(">>") != string::npos)
		 || (prompt.find("|&") != string::npos))
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
int BgCmd(string prompt)
{

	string Command;
	string delimiters = " \t\n";
	string args[MAX_ARG];
	if (prompt.back() == '&')
	{
		prompt.pop_back();
		// Add your code here (execute a in the background)
		
		/* 
		your code
		*/
		
	}
	return -1;
}

