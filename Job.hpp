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

    /// @brief calc the running time of "this".
    /// @return returns the running time
    double getRunningTime();

    /// @brief check if the job terminated every checkIntervals(sec) for maxTimeToWait(sec)
    /// @param maxTimeToWait 
    /// @param checkIntervals 
    /// @return true if the pid is killed, false if maxTimeToWait arrived and the pid is still alive.
    bool waitUntilTerminated(double maxTimeToWait, double checkIntervals);

    /// @brief update the job status to BgRunning and its timestamp accordingly
    void UpdateFromStoppedToBgRunning();

    /// @brief update the job status to FgRunning and its timestamp accordingly
    void UpdateFromStoppedToFgRunning();

    /// @brief update the job status to stopped and its timestamp accordingly 
    void UpdateFromRunningToStopped();

    /// @brief update the job status to FgRunning and its timestamp accordingly
    void UpdateFromBgRunningToFgRunning();
};

#endif

