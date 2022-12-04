#ifndef _JOB_HPP
#define _JOB_HPP

#include "Job.hpp"
#include <string>

#define SIGEXCIST 0
#define EXCIST 0

using namespace std;

Job::Job()
{
    this->PID = NOT_EXCIST;
    this->jobID = NOT_EXCIST;
    this->prompt = "";
    this->command = "";
    this->status = bgRunning;
    this->timeStamp = NOT_EXCIST;
}

Job::Job(int PID, int jobID, string prompt, string command, jobStatus status)
{
    this->PID = PID;
    this->jobID = jobID;
    this->prompt = prompt;
    this->command = command;
    this->status = status;
    time(&(this->timeStamp));
}

/// @brief calc the running time of "this".
/// @return returns the running time
double Job::getRunningTime()
{
    if(status == stopped) // if the job is stopped, its running time is its timeStamp
        return timeStamp;
    else // the job is still running so clac the running time as of this moment.
    {
        time_t start = this->timeStamp;
        time_t end;
        time(&end);
        return difftime(end, start);
    }
}

/// @brief check if the job excist every checkIntervals for maxTimeToWait
/// @param maxTimeToWait 
/// @param checkIntervals 
/// @return true if the pid is killed, false if maxTimeToWait arrived and the pid is still alive.
bool Job::waitUntilTerminated(double maxTimeToWait, double checkIntervals)
{
	while(maxTimeToWait > 0)
	{
		sleep(checkIntervals);
		if(kill(PID, SIGEXCIST) != EXCIST)
			return true;
		maxTimeToWait -= checkIntervals;
	}
	return false;
}

void Job::UpdateFromStoppedToBgRunning()
{
        time_t currentTime;
	    time(&currentTime);
	    timeStamp = difftime(currentTime, timeStamp);
        status = bgRunning;
}

void Job::UpdateFromStoppedToFgRunning()
{
        time_t currentTime;
	    time(&currentTime);
	    timeStamp = difftime(currentTime, timeStamp);
        status = fgRunning;
}

void Job::UpdateFromBgRunningToFgRunning()
{
        status = fgRunning;
}

void Job::UpdateFromRunningToStopped()
{
        timeStamp = getRunningTime();
        status = stopped;
}


#endif