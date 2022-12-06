// signals.cpp
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.hpp"
#include <iostream>
#include "Job.hpp"
#include "Shell.hpp"

using namespace std;

extern Shell *shell;

void SignalHandler_ctrZ(int signal)
{
   cout << "smash: caught ctrl-Z" << endl;
   if(shell->fgJob.PID != NOT_EXCIST)
   {
      if(kill(shell->fgJob.PID, SIGSTOP) == 0)
         cout << "smash: process " << shell->fgJob.PID << " was stopped" << endl;
      
      else cerr << "smash error: kill failed" << endl;
   }
   //else
   //   cout << "smash > " << flush; //NOTE -  make the shell more user friendly
}

void SignalHandler_ctrC(int signal) 
{
   cout << "smash: caught ctrl-C" << endl;
   if(shell->fgJob.PID != NOT_EXCIST)
   {
      if(kill(shell->fgJob.PID, SIGKILL) == 0)
         cout << "smash: process " << shell->fgJob.PID <<  " was killed" << endl;
         
      else cerr << "smash error: kill failed" << endl;
   }
   //else
   //   cout << "smash > " << flush; //NOTE -  make the shell more user friendly
}
