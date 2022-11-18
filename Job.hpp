#ifndef JOB_HPP
#define JOB_HPP
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

using namespace std;

enum jobStatus
{
    running,
    waiting,
    stopped
};

class Job
{
public:

    jobStatus status;
    int PID;
    int jobID;
    string command;
    int secondElapsed;
};

#endif

