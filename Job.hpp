#ifndef JOB_HPP
#define JOB_HPP
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

#define EMPTY -1

using namespace std;

enum jobStatus
{
    fgRunning,
    bgRunning,
    stopped
};

class Job
{
public:
    jobStatus status;
    int PID;
    int jobID;
    string command;
    time_t timeStamp;

    Job();
    Job(int PID, int jobID, string command, jobStatus status);
    double getRunningTime();
};

#endif

