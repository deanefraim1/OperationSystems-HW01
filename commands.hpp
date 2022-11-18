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
#include <vector>
#include <iostream>
#include "Job.hpp"
#include "Shell.hpp"



using namespace std;

#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define ERROR -1

int ExeComp(string lineSize);
int BgCmd(string lineSize);
int ExeCmd(string lineSize, string cmdString);
void ExeExternal(string args[MAX_ARG], string cmdString);

#endif
