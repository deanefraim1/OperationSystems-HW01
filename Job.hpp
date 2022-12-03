#ifndef JOB_HPP
#define JOB_HPP
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

#define NOT_EXCIST -1

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
    pid_t PID;
    int jobID;
    string prompt;
    string command;
    time_t timeStamp;

    Job();
    Job(int PID, int jobID, string prompt, string command, jobStatus status);
    double getRunningTime();
    bool waitUntilTerminated(double maxTimeToWait, double checkIntervals);
};

#endif

