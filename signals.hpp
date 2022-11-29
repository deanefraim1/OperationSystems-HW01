#ifndef _SIGS_HPP
#define _SIGS_HPP
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

/// @brief signal handler function for ctrl-z pressed. stops the job it was sent to
/// @param signal the signal that was sent to the shell (SIGSTOP)
void SignalHandler_ctrZ(int signal);

/// @brief signal handler function for ctrl-c pressed. kill the job it was sent to
/// @param signal the signal that was sent to the shell (SIGKILL)
void SignalHandler_ctrC(int signal);

#endif

