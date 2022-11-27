//		commands.cpp
//********************************************
#include "commands.hpp"
#include <vector>
#include "Job.hpp"
#include <string>
#include <iostream>
#include "Shell.hpp"
#include <regex>
#include <fstream>

#define SIGEXCIST 0
#define EXCIST 0

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
	//else if (cmd == "mkdir")
	//{
 	//	//No need to impliment.
	//}
	/*************************************************/
	
	else if (cmd == "jobs") 
	{
		shell->UpdateJobsList();
		for (int i = 0; i < shell->jobs.size(); i++)
		{
			cout << "[" << shell->jobs[i].jobID << "] " << shell->jobs[i].prompt << " : " << shell->jobs[i].PID << " " << shell->jobs[i].getRunningTime() << " secs"; //TODO: should print the whole command prompt or just the command itdelf?
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
				cout << "smash error: fg: jobs list is empty" << endl; //TODO: cerr??
			else 
				shell->MoveJobToFg(shell->jobs.end());
		}
			
		else if((num_arg != 1) || (!regex_match(args[1], regex("(\\d)+"))))
			cout << "smash error: fg: invalid arguments" << endl; //TODO: cerr??
		else
		{
			int jobIDToFg = atoi(args[1].c_str());
			int jobIndexToFg = shell->GetJobIndexByJobID(jobIDToFg);
			if(jobIndexToFg == NOT_EXCIST)
				cout << "smash error: fg: job-id " << jobIDToFg << " does not exist " << endl; //TODO: cerr??
			else
			{
				shell->MoveJobToFg(shell->jobs.begin() + jobIndexToFg);
				int status;
				waitpid(shell->jobs[jobIndexToFg].PID, &status, 0);
			}
		}
	}
	/*************************************************/
	else if (cmd == "bg") 
	{
  		if(num_arg == 0) //no argument => find the stopped job with maximum job id
		{
			int stoppedJobPIDWithMaxJobID = shell->GetStoppedJobPIDWithMaxJobID();
			if (stoppedJobPIDWithMaxJobID == NOT_EXCIST)
				cout << "smash error: bg: there are no stopped jobs to resume" << endl; //TODO: cerr??
			else
			{
				shell->jobs[stoppedJobPIDWithMaxJobID].status = fgRunning;
				kill(stoppedJobPIDWithMaxJobID, SIGCONT);
				cout << "[" << shell->jobs[stoppedJobPIDWithMaxJobID].jobID << "] " << shell->jobs[stoppedJobPIDWithMaxJobID].prompt << " : " << shell->jobs[stoppedJobPIDWithMaxJobID].PID << endl;
			}
		}
		else if((num_arg != 1) || (!regex_match(args[1], regex("(\\d)+")))) // more than 1 argument or one argument but not a number
			cout << "smash error: bg: invalid arguments" << endl; //TODO: cerr??
		else
		{
			int jobIndexToBg = shell->GetJobIndexByJobID(atoi(args[1].c_str()));
			if (jobIndexToBg == NOT_EXCIST)
				cout << "smash error: bg: job-id " << args[1] << " does not exist" << endl; //TODO: cerr??
			else if(shell->jobs[jobIndexToBg].status != stopped) // the given job is not stopped
				cout << "smash error: bg: job-id " << args[1] << " is already running in the background" << endl; //TODO: cerr??
			else
			{
				shell->jobs[jobIndexToBg].status = fgRunning;
				kill(shell->jobs[jobIndexToBg].PID, SIGCONT);
				cout << "[" << shell->jobs[jobIndexToBg].jobID << "] " << shell->jobs[jobIndexToBg].prompt << " : " << shell->jobs[jobIndexToBg].PID << endl;

			}
		}
	}
	/*************************************************/
	else if (cmd == "quit")
	{
		if(args[1] == "kill") //kill all jobs befor quit the shell
		{
			for (int i = 0; i < shell->jobs.size(); i++)
			{
				cout << "[" << shell->jobs[i].jobID << "] " << shell->jobs[i].prompt << " - Sending SIGTERM...";
				kill(shell->jobs[i].PID, SIGTERM);
				sleep(5);//TODO: do it faster and dont wait 5 sec in every situatoin
				if(kill(shell->jobs[i].PID, SIGEXCIST) == EXCIST)
				{
					cout << " (5 sec passed) Sending SIGKILL...";
					kill(shell->jobs[i].PID, SIGKILL);
				}
				cout << " Done." << endl;
			}
		}
		free(shell);
		exit(0);
	}
	else if (cmd == "kill")
	{
		if(num_arg != 2 || !regex_match(args[1], regex("-(\\d)+")) || !regex_match(args[2], regex("(\\d)+")))
			cout << "smash error: kill: invalid arguments" << endl; //TODO: cerr??
		else
		{
			int sigNum = atoi(args[1].substr(1, args[1].length()).c_str());
			int jobID = atoi(args[2].c_str());
			int jobIndexToKill = shell->GetJobIndexByJobID(jobID);
			if(jobIndexToKill == NOT_EXCIST)
				cout << "smash error: kill: job-id <" << jobID << "> does not exist" << endl; //TODO: cerr??
			else
			{
				kill(shell->jobs[jobIndexToKill].PID, sigNum);
				cout << "signal number " << sigNum << "was sent to pid " << shell->jobs[jobIndexToKill].PID << endl;
			}
		}
	}
	else if (cmd == "diff")
	{
		if(num_arg != 2)
			cout << "smash error: diff: invalid arguments" << endl; //TODO: cerr??
		else
		{
			ifstream file1(args[1], ios::in|ios::binary|ios::ate); //open args[1] file for reading (with seek in the end to check size late), acces him through "file1"
			ifstream file2(args[2], ios::in|ios::binary|ios::ate); //open args[2] file for reading (with seek in the end to check size late), acces him through "file2"
			if(file1.fail() || file2.fail()) // one or more of the files failed to open
				illegal_cmd = true;
			else if(file1.tellg() != file2.tellg()) // the size of the files is different(check position of seek)
				cout << "1" << endl;
			else
			{
				file1.seekg(0, ifstream::beg); // sets the seek back to the begining
				file2.seekg(0, ifstream::beg); //sets the seek back to the begining
				bool isEqual = equal(istreambuf_iterator<char>(file1.rdbuf()),
									 istreambuf_iterator<char>(),
									 istreambuf_iterator<char>(file2.rdbuf()));
				cout << isEqual << endl;
			}
		}
	}
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, prompt, cmd, num_arg);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		cout << "smash error: \"" << prompt << "\"" << endl; //TODO: cerr??
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
void ExeExternal(string args[MAX_ARG], string prompt, string cmd, int num_arg)
{
	int pID;
	char **charArgs = InitStringArrayToCharArray(args, num_arg+1); //for the command +1
	switch (pID = fork())
	{
    	case -1: 
		{
			//fork returned error
				cerr << "smash error: fork failed" << endl; //TODO: cerr??
				free(charArgs);
		}
				
		case 0 :
		{
			// Child Process
         		setpgrp();
				execvp(cmd.c_str(), charArgs);
				cerr << "smash error: exec failed" << endl; //TODO: cerr??
				exit(1);
		}

		default:
		{
			// Parent Proccess
			if(kill(pID, SIGEXCIST) == EXCIST)
			{
				Job newJob;
				if (args[num_arg] == "&")
				{
					newJob = Job(pID, shell->jobs.size() + 1, prompt, cmd, bgRunning);
					shell->InsertJobSorted(newJob);
				}
					
				else
				{
					newJob = Job(pID, shell->jobs.size() + 1, prompt, cmd, fgRunning);
					shell->InsertJobToFg(newJob);
				}
			}
			if(args[num_arg] != "&")
				waitpid(pID, NULL, WUNTRACED);
			free(charArgs);
		}
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

char **InitStringArrayToCharArray(string stringArray[], int size)
{
	char **charArray = (char**)malloc(sizeof(char *) * size);
	for (int i = 0; i < size; i++)
	{
		charArray[i] = strdup(stringArray[i].c_str());
	}
	if(strcmp(charArray[size-1],"&") == 0)
		charArray[size - 1] = NULL;
	else 
		charArray[size] = NULL;
	return charArray;
}
