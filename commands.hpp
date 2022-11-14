#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <csignal>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <list>
#include "Job.hpp"

using namespace std;

#define MAX_LINE_SIZE 80
#define MAX_ARG 20

int ExeComp(string lineSize);
int BgCmd(string lineSize, list<Job> jobs);
int ExeCmd(list<Job> jobs, string lineSize, string cmdString);
void ExeExternal(string args[MAX_ARG], string cmdString);
#endif

