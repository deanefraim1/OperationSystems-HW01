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
   int status;
   waitpid(shell->fgJob.PID, &status, WNOHANG);
   cout << "smash: caught ctrl-Z" << endl;
   if((shell->fgJob.PID != NOT_EXCIST) && WIFSTOPPED(status))
   {
      if(kill(shell->fgJob.PID, SIGSTOP) == 0)
      {
         cout << "smash: process " << shell->fgJob.PID <<  " was stopped" << endl;
         shell->StopFgJob();
      } 
      else cerr << "smash error: kill failed" << endl;
   }
   //else
   //   cout << "smash > " << flush; //NOTE -  make the shell more user friendly
}

void SignalHandler_ctrC(int signal)
{
   int status;
   waitpid(shell->fgJob.PID, &status, WNOHANG);
   cout << "smash: caught ctrl-C" << endl;
   if((shell->fgJob.PID != NOT_EXCIST) && WIFSIGNALED(status))
   {
      if(kill(shell->fgJob.PID, SIGKILL) == 0)
      {
         cout << "smash: process " << shell->fgJob.PID <<  " was killed" << endl;
         shell->ClearFgJob();
      }  
      else cerr << "smash error: kill failed" << endl;
   }
   //else
   //   cout << "smash > " << flush; //NOTE -  make the shell more user friendly
}
