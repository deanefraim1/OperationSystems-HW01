#ifndef _SIGS_HPP
#define _SIGS_HPP
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

void SignalHandler_ctrZ(int signal); //SIGSTOP
void SignalHandler_ctrC(int signal); //SIGKILL

#endif

