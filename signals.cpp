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
   if(shell->fgJob.PID != EMPTY)
   {
      if(kill(shell->fgJob.PID, SIGSTOP) == 0)
      {
         cout << "smash: process " << shell->fgJob.PID <<  " was stopped" << endl;
         shell->fgJob.status = stopped;
         time_t currentTime;
         time(&currentTime);
         shell->fgJob.timeStamp = shell->fgJob.getRunningTime(); //when job stopped the timeStamp becoms her runing time so far.
         shell->InsertJobSorted(shell->fgJob);
         shell->fgJob = Job();
      } 
      else cerr << "smash error: kill failed" << endl; //TODO: cerr??
   }
   else
   {
      cout << "smash > ";
      cout.flush(); //TODO: why i need it?
   }
      
}

void SignalHandler_ctrC(int signal)
{
   cout << "smash: caught ctrl-C" << endl;
   if(shell->fgJob.PID != EMPTY)
   {
      if(kill(shell->fgJob.PID, SIGKILL) == 0)
      {
         cout << "smash: process " << shell->fgJob.PID <<  " was killed" << endl;
         shell->fgJob = Job();
      }  
      else cerr << "smash error: kill failed" << endl; //TODO: cerr??
   }
   else
   {
      cout << "smash > ";
      cout.flush(); //TODO: why i need it?
   }
}
