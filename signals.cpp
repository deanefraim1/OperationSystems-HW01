// signals.cpp
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.hpp"
#include <iostream>

using namespace std;

void SignalHandler_ctrZ(int signal)
{
   cout << "asdasdassdasda";
}

void SignalHandler_ctrC(int signal)
{

}
