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

int ExeComp(string prompt);
int ExeCmd(string prompt);
char **InitStringArrayToCharArray(string stringArray[], int size);
void ExeExternal(string args[MAX_ARG], string cmd, int num_arg);

#endif
