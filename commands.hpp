#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <csignal>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <list>
#include "Job.hpp"

using namespace std;

#define MAX_LINE_SIZE 80
#define MAX_ARG 20

int ExeComp(char* lineSize);
int BgCmd(char* lineSize, list<Job> jobs);
int ExeCmd(list<Job> jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);
#endif

