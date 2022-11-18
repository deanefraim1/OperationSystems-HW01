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

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in OR external commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
extern Shell shell;

int ExeCmd(string prompt, string cmdString)
{
	string cmd;
	string args[MAX_ARG];
	string delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
	char *tmp = strtok(strdup(prompt.c_str()), strdup(delimiters.c_str()));
	if(tmp != NULL)
		cmd = tmp;
	if(cmd.empty()) return 0; //TODO: or null returned from strtok???
	args[0] = cmd;
	for (i = 1; i < MAX_ARG; i++)
	{
		char *tmp = strtok(NULL, strdup(delimiters.c_str()));
		if(tmp == NULL)
			break;
		args[i] = tmp;
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
				string temp = shell.pwd.substr(0, shell.pwd.find_last_of('/'));
				if (chdir(temp.c_str()) == ERROR)
					cerr << "cd";
				else
				{
					shell.lastPwd = shell.pwd;
					shell.pwd = args[1];
				}
			}
			else if(args[1] == "-")
			{
				if(shell.lastPwd.empty())
					cout << "smash error: cd: OLDPWD not set" << endl;
				else
				{
					chdir(shell.lastPwd.c_str());
					swap(shell.pwd, shell.lastPwd);
				}
			}
			else 
			{
				if(chdir(args[1].c_str()) == ERROR) cerr << "cd";
				else
				{
					shell.lastPwd = shell.pwd;
					shell.pwd = args[1];
				}
			}
		}
		else
		{
			cout << "smash error: cd: too many arguments" << endl;
			illegal_cmd = true;
		}
	}

	/*************************************************/
	else if (cmd == "pwd") 
	{
		char buffer[MAX_LINE_SIZE];
		if(getcwd(buffer, MAX_LINE_SIZE) == NULL) cerr << "pwd";
		shell.pwd = buffer;
		cout << shell.pwd << endl;
	}

	/*************************************************/
	else if (cmd == "mkdir")
	{
 		//No need to impliment.
	}
	/*************************************************/
	
	else if (cmd == "jobs") 
	{
		for (int i = 0; i < shell.jobs.size(); i++)
		{
			cout << "[" << shell.jobs[i].jobID << "] " << shell.jobs[i].command << " : " << shell.jobs[i].PID << " " << shell.jobs[i].secondElapsed << "secs";
			if(shell.jobs[i].status == stopped)
				cout << "stopped";
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
		bool jobFound = false;
		if ((num_arg == 0) && (shell.jobs.empty()))
			cout << "smash error: fg: jobs list is empty" << endl;
		else if((num_arg != 1) || (!regex_match(args[1], regex("(\\d)+"))))
			cout << "smash error: fg: invalid arguments" << endl;
		else
		{
			int jobIDToFg = atoi(args[1].c_str());
			for (int i = 0; i < shell.jobs.size(); i++)
			{
				if(shell.jobs[i].jobID == jobIDToFg)
				{
					Job jobToFg = shell.jobs[i];
					shell.jobs.erase(shell.jobs.begin() + i);
					for (int j = 0; j < shell.jobs.size(); j++)
					{
						if(shell.jobs[j].jobID > shell.fgJob.jobID)
						{
							shell.jobs.insert(shell.jobs.begin() + j, shell.fgJob);
							shell.jobs[j].status = waiting;
							break;
						}
					}
					shell.fgJob = jobToFg;
					shell.fgJob.status = running;
					jobFound = true;
					break;
				}
			}
			if(!jobFound)
			{
				cout << "smash error: fg: job-id <" << jobIDToFg << " > does not exist " << endl;
			}
		}
	}
	/*************************************************/
	else if (cmd == "bg") 
	{
  		
	}
	/*************************************************/
	else if (cmd == "quit")
	{
   		
	}
	else if (cmd == "kill")
	{
		if(num_arg != 2 || regex_match(args[1], regex("-(\\d)+")) || regex_match(args[2], regex("(\\d)+"))) 
			cout << "smash error: kill: invalid arguments";
		else
		{
			int sigNum = atoi(args[1].substr(1, args[1].length()).c_str());
			int jobID = atoi(args[2].c_str());
			bool jobFound = false;
			for (int i = 0; i < shell.jobs.size(); i++)
			{
				if(shell.jobs[i].jobID == jobID)
				{
					kill(shell.jobs[i].PID, sigNum);
					jobFound = true;
					cout << "signal number " << sigNum << "was sent to pid " << shell.jobs[i].PID << endl;
					break;
				}
			}
			if(!jobFound)
				cout << "smash error: kill: job-id <" << jobID << "> does not exist" << endl;
		}
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
int BgCmd(string lineSize)
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

